from dataclasses import dataclass

from PyQt6 import uic, QtCore
from PyQt6.QtWidgets import QDialog


@dataclass
class InsertElementData:
    index: int
    text: str


class InsertElementDialog(QDialog):
    element_selected = QtCore.pyqtSignal(InsertElementData)

    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi("insert_element_dialog.ui", self)
        self.accepted.connect(self.on_accepted)

    def on_accepted(self):
        data = InsertElementData(self.spinBox.value(), self.lineEdit.text())
        self.element_selected.emit(data)
        self.close()

    def set_max_index(self, max_index):
        self.spinBox.setMaximum(max_index)
