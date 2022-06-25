from dataclasses import dataclass

import numpy as np
from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtWidgets import QCheckBox, QWidget, QHBoxLayout, QTableWidgetItem

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

    def __init__(self, parent=None, colored_cells: bool = False, checkable: bool = False):
        super().__init__(parent=parent, colored_cells=colored_cells)
        self._vertically_checkable = checkable
        self._horizontally_checkable = checkable
        self._x_offset = 1 if checkable else 0
        self._y_offset = 1 if checkable else 0
        self.row_state_changed.connect(lambda state: self._mark_row_as_checked(state.index, state.checked))
        self.column_state_changed.connect(lambda state: self._mark_column_as_checked(state.index, state.checked))

    @MatrixView.matrix.setter
    def matrix(self, matrix: np.ndarray):
        # call the original setter
        MatrixView.matrix.fset(self, matrix)
        self.inject_checkboxes()

    @MatrixView.horizontal_header.setter
    def horizontal_header(self, header: list):
        MatrixView.horizontal_header.fset(self, header)
        if self._vertically_checkable:
            self.setHorizontalHeaderItem(0, QTableWidgetItem(""))

    @MatrixView.vertical_header.setter
    def vertical_header(self, header: list):
        MatrixView.vertical_header.fset(self, header)
        if self._horizontally_checkable:
            self.setVerticalHeaderItem(0, QTableWidgetItem(""))

    @property
    def checkable(self) -> bool:
        return self._vertically_checkable and self._horizontally_checkable

    @checkable.setter
    def checkable(self, flag: bool):
        self._vertically_checkable = flag
        self._horizontally_checkable = flag
        if flag:
            self._x_offset = 1
            self._y_offset = 1
            self.inject_checkboxes()
        elif self.findChild(CenteredCheckBox):
            self._x_offset = 0
            self._y_offset = 0
            self.removeRow(0)
            self.removeColumn(0)

    @property
    def vertically_checkable(self) -> bool:
        return self._vertically_checkable
    
    @vertically_checkable.setter
    def vertically_checkable(self, flag: bool):
        self._vertically_checkable = flag
        if flag:
            self._y_offset = 1
            self.inject_checkboxes()
        elif self.findChild(CenteredCheckBox):
            self._y_offset = 0
            self.removeColumn(0)
    
    @property
    def horizontally_checkable(self) -> bool:
        return self._horizontally_checkable

    @horizontally_checkable.setter
    def horizontally_checkable(self, flag: bool):
        self._horizontally_checkable = flag
        if flag:
            self._x_offset = 1
            self.inject_checkboxes()
        elif self.findChild(CenteredCheckBox):
            self._x_offset = 0
            self.removeRow(0)

    def column_checked(self, column: int) -> bool:
        checkbox = self.cellWidget(0, column + self._x_offset)
        return checkbox.checked

    def set_column_checked(self, column: int, checked: bool):
        checkbox = self.cellWidget(0, column + self._x_offset)
        checkbox.checked = checked
        self._mark_column_as_checked(column, checked)

    def _mark_column_as_checked(self, column: int, checked: bool):
        flags= Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsEditable if checked else Qt.ItemFlag.NoItemFlags
        for row in range(self._y_offset, self.rowCount()):
            if checked and not self.row_checked(row - self._y_offset):
                continue
            self.item(row, column + self._x_offset).setFlags(flags)

    def row_checked(self, row: int) -> bool:
        checkbox = self.cellWidget(row + self._y_offset, 0)
        return checkbox.checked

    def set_row_checked(self, row: int, checked: bool):
        checkbox = self.cellWidget(row + self._y_offset, 0)
        checkbox.checked = checked
        self._mark_row_as_checked(row, checked)

    def _mark_row_as_checked(self, row: int, checked: bool):
        flags= Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsEditable if checked else Qt.ItemFlag.NoItemFlags
        for col in range(self._x_offset, self.columnCount()):
            if checked and not self.column_checked(col - self._x_offset):
                continue
            self.item(row + self._y_offset, col).setFlags(flags)

    def inject_checkboxes(self):
        # insert column on index 0 and row on index 0
        # all items in both columns and rows are checkboxes
        if self._horizontally_checkable:
            self.insertColumn(0)
            self.setVerticalHeaderItem(0, QTableWidgetItem(""))
            for row in range(0, self.rowCount()):
                widget = CenteredCheckBox()
                widget.state_changed.connect(lambda state, row=row: self.row_state_changed.emit(RowState(state, row)))
                self.setCellWidget(row, 0, widget)

        if self._vertically_checkable:
            self.insertRow(0)
            self.setHorizontalHeaderItem(0, QTableWidgetItem(""))
            for col in range(self._x_offset, self.columnCount()):
                widget = CenteredCheckBox()
                widget.state_changed.connect(lambda state, col=col-self._x_offset: self.column_state_changed.emit(ColumnState(state, col)))
                self.setCellWidget(0, col, widget)


class CenteredCheckBox(QWidget):
    # signal state changed is emitted when the checkbox is checked or unchecked
    state_changed = pyqtSignal(bool)

    def __init__(self, parent=None, checked=True):
        super().__init__(parent)
        checkbox = QCheckBox()
        layout = QHBoxLayout(self)
        layout.addWidget(checkbox)
        layout.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.setContentsMargins(0, 0, 0, 0)
        checkbox.setChecked(checked)
        checkbox.stateChanged.connect(self.state_changed.emit)

    @property
    def checked(self) -> bool:
        return self.findChild(QCheckBox).isChecked()

    @checked.setter
    def checked(self, checked: bool):
        self.findChild(QCheckBox).setChecked(checked)
