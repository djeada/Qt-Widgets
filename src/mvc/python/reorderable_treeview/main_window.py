from PyQt6 import QtWidgets, uic

from reorderable_tree_model import ReorderableTreeModel
from tree_model import TreeModel, TreeItem


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        model = ReorderableTreeModel()
        model.appendRow(TreeItem(["Item 1"]))
        model.appendRow(TreeItem(["Item 2"]))

        item = model.itemFromIndex(model.index(0, 0))
        item.append_child(TreeItem(["Item 1.1"]))
        item.append_child(TreeItem(["Item 1.2"]))
        item.append_child(TreeItem(["Item 1.3"]))

        item = model.itemFromIndex(model.index(1, 0))
        item.append_child(TreeItem(["Item 2.1"]))
        item.append_child(TreeItem(["Item 2.2"]))
        item.append_child(TreeItem(["Item 2.3"]))

        self.treeView.setModel(model)

        self.show()
