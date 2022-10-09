from PyQt6 import QtWidgets, uic
from tree_model import TreeModel, TreeItem


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        model = TreeModel()
        model.appendRow(TreeItem(["Elements"]))
        model.appendRow(TreeItem(["Items"]))
        self.treeView.setModel(model)

        self.show()
