from PyQt6.QtCore import Qt, QModelIndex
from PyQt6.QtGui import QIcon, QStandardItem, QStandardItemModel
from PyQt6.QtWidgets import QTreeView, QAbstractItemView, QHeaderView

from emoji_picker_delegate import EmojiPickerDelegate


class EmojiPickerItem(QStandardItem):
    def __init__(self, category, column_count):
        super().__init__()
        self.itemCategory = category
        self.setColumnCount(column_count)
        self.setCategory(category)

    def setCategory(self, category):
        self.itemCategory = category
        self.setText(category.name)
        for i in range(0, len(category.emojis) // self.columnCount()):
            items = []
            for j in range(0, self.columnCount()):
                next_index = j + i * self.columnCount()
                if next_index >= len(category.emojis):
                    break
                icon = QIcon(category.emojis[next_index].iconPath)
                items.append(QStandardItem(icon, ""))
            self.appendRow(items)
    
    def setColumnCount(self, count):
        QStandardItem.setColumnCount(self, count)
        self.setCategory(self.itemCategory)

    def category(self):
        return self.itemCategory

    
class EmojiPickerModel(QStandardItemModel):
    def __init__(self, parent):
        super().__init__(parent)
        
    def appendRow(self, category):
        QStandardItemModel.appendRow(self, EmojiPickerItem(category, self.columnCount()))

    def clear(self):
        QStandardItemModel.removeRows(self, 0, self.rowCount())

    def setColumnCount(self, count):
        QStandardItemModel.setColumnCount(self, count)
        for item in self.findItems("", Qt.MatchFlag.MatchContains):
            item.setColumnCount(count)


class EmojiPickerTree(QTreeView):
    def __init__(self, parent):
        super().__init__(parent)
        self.setHeaderHidden(True)
        self.setItemsExpandable(False)
        self.setStyleSheet("QTreeView::branch {  border-image: url(none.png); }")
        self.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectItems)
        self.setItemDelegate(EmojiPickerDelegate(self))
        self.header().setStretchLastSection(False)
    
    def setModel(self, model):
        super().setModel(model)
        self.expandAll()
        self.setIndentation(3)
        self.header().setSectionResizeMode(0, QHeaderView.ResizeMode.Fixed)
        for column in range(0, model.columnCount()):
            self.header().setSectionResizeMode(column, QHeaderView.ResizeMode.Fixed)
            self.header().resizeSection(column, 50)
        for row in range(0, model.rowCount()):
            self.setFirstColumnSpanned(row, QModelIndex(), True)

    def model(self):
        return super().model()
