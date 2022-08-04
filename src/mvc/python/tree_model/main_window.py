from PyQt6 import QtWidgets, uic
from tree_model import TreeModel


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        model = TreeModel(["Col A", "Col B", "Col C"])
        model.appendRow(["Elements"])
        model.appendRow(["Items"])
        self.treeView.setModel(model)

        self.show()
