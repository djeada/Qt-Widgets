from PyQt6.QtCore import QAbstractItemModel, QModelIndex, QObject, Qt, QVariant


class TreeItem:
    def __init__(self, data, parent=None):
        self._data = data
        self.parent = parent
        self.children = []

        if parent is not None:
            parent.append_child(self)

    @property
    def data(self):
        return self._data

    @data.setter
    def data(self, data):
        self._data = data

    def column_count(self):
        return len(self.data)

    def append_column(self, value):
        self.data.append(value)

    def remove_column(self, index):
        self.data.pop(index)

    def append_child(self, child):
        current_parent = child.parent

        if current_parent is not None:
            row = child.row()
            current_parent.remove_row(row)

        child.parent = self
        self.children.append(child)

    def child(self, row):
        if row < 0 or row >= len(self.children):
            return None

        return self.children[row]

    def child_to_row(self, child):
        if child not in self.children:
            return -1

        return self.children.index(child)

    def child_count(self):
        return len(self.children)

    def children_column_count(self):
        max_count = 0
        for child in self.children:
            max_count = max(max_count, child.column_count())

        return max_count

    def remove_row(self, row):
        if row < 0 or row >= len(self.children):
            return False

        self.children.pop(row)
        return True

    def remove_all_children(self):
        self.children.clear()

    def row(self):
        if self.parent is not None:
            return self.parent.child_to_row(self)

        return 0


class TreeModel(QAbstractItemModel):
    def __init__(self, parent=None, read_only=False):
        super().__init__(parent)
        self.headers = []
        self.root = TreeItem(["root"])
        self.read_only = read_only

    def data(self, index, role=Qt.ItemDataRole.DisplayRole):
        if not index.isValid():
            return QVariant()

        if role == Qt.ItemDataRole.DisplayRole or role == Qt.ItemDataRole.EditRole:
            item = self.itemFromIndex(index)
            column = index.column()
            if column < item.column_count():
                return item.data[column]

        return QVariant()

    def setData(self, index, value, role=Qt.ItemDataRole.EditRole):
        if not index.isValid() or role != Qt.ItemDataRole.EditRole:
            return False

        item = self.itemFromIndex(index)
        try:
            item.data[index.column()] = value
        except IndexError:
            return False

        self.dataChanged.emit(index, index)
        return True

    def headerData(self, section, orientation, role=Qt.ItemDataRole.DisplayRole):
        if (
            role == Qt.ItemDataRole.DisplayRole
            and orientation == Qt.Orientation.Horizontal
        ):
            if section < len(self.headers):
                return self.headers[section]

        return QVariant()

    def setHeaderData(self, section, orientation, value, role=Qt.ItemDataRole.EditRole):
        if (
            role == Qt.ItemDataRole.EditRole
            and orientation == Qt.Orientation.Horizontal
        ):
            if section < len(self.headers):
                self.headers[section] = value
                return True

        return False

    def flags(self, index):
        if not index.isValid():
            return Qt.ItemFlag.NoItemFlags

        flags = Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable

        if not self.read_only:
            flags |= Qt.ItemFlag.ItemIsEditable

        return flags

    def hasIndex(self, row, column, parent=QModelIndex()):
        if not self.hasParent(parent):
            return False

        parent_item = self.itemFromIndex(parent)
        if parent_item.child(row) is not None:
            return True

        return False

    def index(self, row, column, parent=QModelIndex()):
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        parent_item = self.itemFromIndex(parent)
        child_item = parent_item.child(row)
        if child_item is not None:
            return self.createIndex(row, column, child_item)

        return QModelIndex()

    def item(self, row, column, parent=QModelIndex()):
        return self.itemFromIndex(self.index(row, column, parent))

    def itemFromIndex(self, index):
        if index.isValid():
            return index.internalPointer()

        return self.root

    def parent(self, index):
        if not index.isValid():
            return QModelIndex()

        child_item = self.itemFromIndex(index)
        parent_item = child_item.parent

        if parent_item == self.root:
            return QModelIndex()

        return self.createIndex(parent_item.row(), 0, parent_item)

    def rowCount(self, parent=QModelIndex()):
        if not self.hasParent(parent):
            return 0

        parent_item = self.itemFromIndex(parent)
        return parent_item.child_count()

    def columnCount(self, parent=QModelIndex()):
        if not self.hasParent(parent):
            return 0

        parent_item = self.itemFromIndex(parent)
        return parent_item.children_column_count()

    def hasParent(self, parent):
        if parent.isValid():
            return True

        return self.root is not None

    def insertRows(self, row, count, parent=QModelIndex()):

        if not self.hasParent(parent):
            return False

        parent_item = self.itemFromIndex(parent)
        self.beginInsertRows(parent, row, row + count - 1)

        if row < 0 or row > parent_item.child_count():
            self.endInsertRows()
            return False

        for i in range(count):
            try:
                item = TreeItem([], parent_item)
                parent_item.children.insert(row + i, item)
            except IndexError:
                self.endInsertRows()
                return False

        self.endInsertRows()
        return True

    def insertRow(self, row, parent=QModelIndex()):
        return self.insertRows(row, 1, parent)

    def removeRows(self, row, count, parent=QModelIndex()):
        if not self.hasParent(parent):
            return False

        parent_item = self.itemFromIndex(parent)
        self.beginRemoveRows(parent, row, row + count - 1)

        if row < 0 or row + count > parent_item.child_count():
            self.endRemoveRows()
            return False

        for i in range(count):
            try:
                parent_item.children.pop(row)
            except IndexError:
                self.endRemoveRows()
                return False

        self.endRemoveRows()
        return True

    def removeRow(self, row, parent=QModelIndex()):
        return self.removeRows(row, 1, parent)

    def appendRows(self, items, parent=QModelIndex()):
        if not self.hasParent(parent):
            parent = QModelIndex()

        parent_item = self.itemFromIndex(parent)
        for item in items:
            parent_item.append_child(item)

    def appendRow(self, item, parent=QModelIndex()):
        return self.appendRows([item], parent)

    def insertColumns(self, column, count, parent=QModelIndex()):
        if not self.hasParent(parent):
            return False

        parent_item = self.itemFromIndex(parent)
        self.beginInsertColumns(parent, column, column + count - 1)

        if column < 0 or column > parent_item.column_count():
            self.endInsertColumns()
            return False

        for i in range(count):
            try:
                parent_item.data.insert(column + i, "")
            except IndexError:
                self.endInsertColumns()
                return False

        self.endInsertColumns()
        return True

    def insertColumn(self, column, parent=QModelIndex()):
        return self.insertColumns(column, 1, parent)

    def removeColumns(self, column, count, parent=QModelIndex()):
        if not self.hasParent(parent):
            return False

        parent_item = self.itemFromIndex(parent)
        self.beginRemoveColumns(parent, column, column + count - 1)

        if column < 0 or column + count > parent_item.column_count():
            self.endRemoveColumns()
            return False

        for i in range(count):
            try:
                parent_item.data.pop(column)
            except IndexError:
                self.endRemoveColumns()
                return False

        self.endRemoveColumns()
        return True

    def removeColumn(self, column, parent=QModelIndex()):
        return self.removeColumns(column, 1, parent)
