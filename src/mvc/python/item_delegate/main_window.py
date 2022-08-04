from custom_delegate import CustomDelegate
from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import QStringListModel


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        model = QStringListModel(self)
        model.setStringList(
            [
                "Item 1",
                "74",
                "Item 3",
                "Item 4",
                "Item 5",
                "Item 6",
                "Item 7",
                "Item 8",
                "Item 9",
            ]
        )
        self.listView.setModel(model)
        self.listView.setItemDelegate(CustomDelegate(self))
        self.show()
