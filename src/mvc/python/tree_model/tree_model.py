from PyQt6.QtCore import QModelIndex, QVariant, Qt, QAbstractItemModel, QObject


class TreeItem(QObject):
    def __init__(self, data, parent=None):
        super().__init__(parent)
        self._data = data
        self.parent_item = parent
        self.child_items = []

    def data(self, column=None):
        if column is None:
            return self._data
        if column < 0 or column >= self.column_count():
            return None
        return self._data[column]

    def setData(self, column, value):
        if column < 0 or column >= self.column_count():
            return
        self._data[column] = value

    def append_child(self, item):
        if not item:
            return
        current_parent = item.parent()
        if current_parent:
            current_parent.remove_child(item)
        item.setParent(self)
        self.child_items.append(item)

    def child(self, row):
        if row < 0 or row >= len(self.child_items):
            return None
        return self.child_items[row]

    def child_from_row(self, child):
        return self.child_items.indexOf(child)

    def children_items(self):
        return self.child_items

    def row_count(self):
        return len(self.child_items)

    def column_count(self):
        return len(self._data)

    def children_column_count(self):
        max_count = 0
        for child in self.child_items:
            max_count = max(max_count, child.column_count())
        return max_count

    def parent(self):
        return self.parent_item

    def row(self):
        if self.parent_item:
            return self.parent_item.child_items.index(self)
        return 0

    def remove_row(self, row):
        if row < 0 or row >= self.row_count():
            return
        self.child_items.remove(row)

    def remove_rows(self, row, count):
        for i in range(count):
            self.child_items.remove(row)

    def remove_child(self, child):
        if child in self.child_items:
            self.child_items.remove(child)

    def remove_all_children(self):
        self.child_items.clear()


class TreeModel(QAbstractItemModel):
    def __init__(self, headers, parent=None):
        super().__init__(parent)
        root_data = [header for header in headers]
        self.root_item = TreeItem(root_data)
        self.readOnly = False

    def setReadOnly(self, flag):
        self.readOnly = flag

    def isReadOnly(self):
        return self.readOnly

    def columnCount(self, parent):
        if parent.isValid():
            return parent.internalPointer().children_column_count()
        return self.root_item.column_count()

    def data(self, index, role):
        if not index.isValid():
            return QVariant()

        if role == Qt.ItemDataRole.DisplayRole or role == Qt.ItemDataRole.EditRole:
            item = self.itemFromIndex(index)
            return item.data(index.column())

        return QVariant()

    def flags(self, index):
        if not index.isValid():
            return Qt.ItemFlag.NoItemFlags
        if self.readOnly:
            return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable
        if self.hasChildren(index):
            return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable
        else:
            return (
                Qt.ItemFlag.ItemIsEnabled
                | Qt.ItemFlag.ItemIsSelectable
                | Qt.ItemFlag.ItemIsEditable
            )
        return Qt.ItemFlag.ItemIsEnabled

    def headerData(self, section, orientation, role):
        if (
            orientation == Qt.Orientation.Horizontal
            and role == Qt.ItemDataRole.DisplayRole
        ):
            return self.root_item.data(section)
        return QVariant()

    def index(self, row, column, parent):
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        parent_item = (
            self.root_item if not parent.isValid() else parent.internalPointer()
        )
        child_item = parent_item.child(row)

        if child_item:
            return self.createIndex(row, column, child_item)

        return QModelIndex()

    def parent(self, index):
        if not index.isValid():
            return QModelIndex()

        child_item = index.internalPointer()
        parent_item = child_item.parent()

        if parent_item == self.root_item:
            return QModelIndex()

        return self.createIndex(parent_item.row(), 0, parent_item)

    def rowCount(self, parent):
        if parent.column() > 0:
            return 0
        if not parent.isValid():
            parent_item = self.root_item
        else:
            parent_item = parent.internalPointer()
        return parent_item.row_count()

    def appendRow(self, data):
        self.root_item.append_child(TreeItem(data, self.root_item))

    def setHorizontalHeaderLabels(self, labels):
        self.root_item.setData(labels)

    def itemFromIndex(self, index):
        if index.isValid():
            item = index.internalPointer()
        if item:
            return item
        return self.root_item

    def item(self, row, column):
        return self.itemFromIndex(self.index(row, column))

    def indexFromItem(self, item):
        if item == self.root_item:
            return QModelIndex()
        return self.createIndex(item.row(), 0, item)

    def removeColumns(self, position, columns, parent):
        self.beginRemoveColumns(parent, position, position + columns - 1)
        try:
            self.root_item.removeColumns(position, columns)
        except Exception as e:
            self.endRemoveColumns()
            return False
        self.endRemoveColumns()

        if self.root_item.column_count() == 0:
            self.removeRows(0, self.rowCount())

        return True

    def removeRows(self, position, rows, parent):
        parent_item = self.itemFromIndex(parent)
        if not parent_item:
            return False
        self.beginRemoveRows(parent, position, position + rows - 1)
        try:
            parent_item.remove_rows(position, rows)

        except Exception as e:
            self.endRemoveRows()
            return False
        self.endRemoveRows()

        return True

    def setData(self, index, value, role):
        if role != Qt.ItemDataRole.EditRole:
            return False
        item = self.itemFromIndex(index)
        try:
            item.setData(index.column(), value)
        except Exception as e:
            return False
        self.dataChanged.emit(
            index, index, [Qt.ItemDataRole.DisplayRole, Qt.ItemDataRole.EditRole]
        )
        return True

    def setHeaderData(self, section, orientation, value, role):
        if role != Qt.ItemDataRole.EditRole or orientation != Qt.Orientation.Horizontal:
            return False
        try:
            self.root_item.setData(section, value)
        except Exception as e:
            return False
        self.headerDataChanged.emit(orientation, section, section)
        return True

    def insertColumns(self, position, columns, parent):
        self.beginInsertColumns(parent, position, position + columns - 1)
        try:
            self.root_item.insertColumns(position, columns)
        except Exception as e:
            self.endInsertColumns()
            return False
        self.endInsertColumns()
        return True

    def insertRows(self, position, rows, parent):
        parent_item = self.itemFromIndex(parent)
        if not parent_item:
            return False
        self.beginInsertRows(parent, position, position + rows - 1)
        try:
            parent_item.insertRows(position, rows, self.root_item.column_count())
        except Exception as e:
            self.endInsertRows()
            return False
        self.endInsertRows()
        return True
