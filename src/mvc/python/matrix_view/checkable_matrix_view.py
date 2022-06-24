from dataclasses import dataclass

import numpy as np
from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtWidgets import QCheckBox, QWidget, QHBoxLayout

from matrix_view import MatrixView


@dataclass
class VectorState:
    checked: bool
    index: int


class RowState(VectorState):
    pass


class ColumnState(VectorState):
    pass


class CheckableMatrixView(MatrixView):
    # emit signal when row or column is checked
    row_state_changed = pyqtSignal(RowState)
    column_state_changed = pyqtSignal(ColumnState)

    def __init__(self, colored_cells: bool = False, checkable: bool = False, parent=None):
        super().__init__(colored_cells=colored_cells, parent=parent)
        self._checkable = checkable

    @MatrixView.matrix.setter
    def matrix(self, matrix: np.ndarray):
        # call the original setter
        MatrixView.matrix.fset(self, matrix)
        if self._checkable:
            self.inject_checkboxes()

    @property
    def checkable(self) -> bool:
        return self._checkable

    @checkable.setter
    def checkable(self, flag: bool):
        self._checkable = flag
        if flag:
            self.inject_checkboxes()
        elif self.findChild(CenteredCheckBox):
            self.removeRow(0)
            self.removeColumn(0)

    def column_checked(self, column: int) -> bool:
        checkbox = self.cellWidget(0, column + 1)
        return checkbox.checked

    def set_column_checked(self, column: int, checked: bool):
        checkbox = self.cellWidget(0, column + 1)
        checkbox.checked = checked

    def row_checked(self, row: int) -> bool:
        checkbox = self.cellWidget(row + 1, 0)
        return checkbox.checked

    def set_row_checked(self, row: int, checked: bool):
        checkbox = self.cellWidget(row + 1, 0)
        checkbox.checked = checked

    def inject_checkboxes(self):
        # insert column on index 0 and row on index 0
        # all items in both columns and rows are checkboxes
        self.insertRow(0)
        self.insertColumn(0)

        for row in range(1, self.rowCount()):
            widget = CenteredCheckBox()
            widget.state_changed.connect(lambda state: self.row_state_changed.emit(RowState(state, row - 1)))
            self.setCellWidget(row, 0, widget)
        for col in range(1, self.columnCount()):
            widget = CenteredCheckBox()
            widget.state_changed.connect(lambda state: self.column_state_changed.emit(ColumnState(state, col - 1)))
            self.setCellWidget(0, col, widget)


class CenteredCheckBox(QWidget):
    # signal state changed is emitted when the checkbox is checked or unchecked
    state_changed = pyqtSignal(bool)

    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QHBoxLayout(self)
        layout.addWidget(QCheckBox())
        layout.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.setContentsMargins(0, 0, 0, 0)
        self.findChild(QCheckBox).stateChanged.connect(self.state_changed.emit)

    @property
    def checked(self) -> bool:
        return self.findChild(QCheckBox).isChecked()

    @checked.setter
    def checked(self, checked: bool):
        self.findChild(QCheckBox).setChecked(checked)
