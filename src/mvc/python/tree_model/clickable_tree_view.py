from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QAbstractItemView, QMenu, QTreeView
from tree_model import TreeItem


class ClickableTreeView(QTreeView):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setContextMenuPolicy(Qt.ContextMenuPolicy.CustomContextMenu)
        self.customContextMenuRequested.connect(self.contextMenuEvent)
        self.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

    def contextMenuEvent(self, pos):
        index = self.indexAt(pos)
        if not index.isValid():
            return
        menu = QMenu()
        menu.addAction("Add Child")
        menu.addAction("Remove Item")
        menu.addAction("Edit Item")
        selectedAction = menu.exec(self.mapToGlobal(pos))
        if not selectedAction:
            return
        value = menu.actions().index(selectedAction)
        if value == 0:
            self.addChild(index)
        elif value == 1:
            self.removeItem(index)
        elif value == 2:
            self.editItem(index)
        else:
            pass

    def model(self):
        return super().model()

    def setModel(self, model):
        super().setModel(model)

    def addChild(self, index):
        model = self.model()
        model.itemFromIndex(index).append_child(
            TreeItem(["New Item"], model.itemFromIndex(index))
        )
        self.expandAll()

    def removeItem(self, index):
        model = self.model()
        model.removeRow(index.row(), index.parent())

    def editItem(self, index):
        self.edit(index)
