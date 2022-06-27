from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import QDir, QStringListModel
from PyQt6.QtWidgets import QAbstractItemView

from insert_element_dialog import InsertElementDialog


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        model = QStringListModel(self)
        model.setStringList(["Item 1", "Item 2", "Item 3"])
        self.listView.setModel(model)

        self.listView.setEditTriggers(
            QAbstractItemView.EditTrigger.DoubleClicked
            | QAbstractItemView.EditTrigger.SelectedClicked
        )

        self.listView.setSelectionMode(QAbstractItemView.SelectionMode.MultiSelection)
        self.listView.setDragEnabled(True)
        self.listView.setAcceptDrops(True)
        self.listView.setDropIndicatorShown(True)
        self.listView.setDragDropMode(QAbstractItemView.DragDropMode.InternalMove)

        self.insertButton.clicked.connect(self.insert_element)
        self.removeButton.clicked.connect(self.remove_element)
        self.show()

    def insert_element(self):
        dialog = InsertElementDialog(self)
        dialog.set_max_index(self.listView.model().rowCount())
        dialog.element_selected.connect(self.insert_element_data)
        dialog.show()

    def insert_element_data(self, data):
        self.listView.model().insertRows(data.index, 1)
        self.listView.model().setData(
            self.listView.model().index(data.index), data.text
        )

    def remove_element(self):
        indexes = self.listView.selectionModel().selectedIndexes()
        for index in indexes:
            self.listView.model().removeRow(index.row())
