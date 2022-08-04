import re
from typing import List, Union

import numpy as np
from PyQt6.QtGui import QColor
from PyQt6.QtWidgets import QTableWidget, QTableWidgetItem


class MatrixView(QTableWidget):
    def __init__(self, parent=None, colored_cells: bool = False):
        super().__init__(parent)
        # hide headers
        self.verticalHeader().hide()
        self.horizontalHeader().hide()
        self._precision = 5
        self._colored_cells = colored_cells
        self._matrix = np.array([])
        self.itemChanged.connect(self.apply_color_background)
        # disable selection
        self.setSelectionMode(QTableWidget.SelectionMode.NoSelection)

    @property
    def matrix(self) -> np.ndarray:
        return self._matrix

    @matrix.setter
    def matrix(self, matrix: np.ndarray):
        self._matrix = matrix

        # clear previous content
        self.clearContents()
        self.blockSignals(True)

        if len(matrix.shape) == 1:
            self.setRowCount(1)
            self.setColumnCount(matrix.shape[0])
            # if matrix is 1D, make it 2D with a single row
            matrix = matrix.reshape(1, matrix.shape[0])
        elif len(matrix.shape) == 2:
            self.setRowCount(matrix.shape[0])
            self.setColumnCount(matrix.shape[1])
        else:
            raise ValueError("MatrixView only supports 1D and 2D matrices")

        for i, row in enumerate(matrix):
            for j, value in enumerate(row):
                item = QTableWidgetItem(self._value_to_string(value))
                self.setItem(i, j, item)

        self.apply_color_background()
        self.blockSignals(False)

    @property
    def colored_cells(self) -> bool:
        return self._colored_cells

    @colored_cells.setter
    def colored_cells(self, flag: bool):
        self._colored_cells = flag
        if flag:
            self.apply_color_background()
            return

        for row in range(self.rowCount()):
            for col in range(self.columnCount()):
                self.set_item_color(row, col, QColor(0, 0, 0, 0))

    def apply_color_background(self):
        if not self.colored_cells:
            return
        self.blockSignals(True)
        colors = [
            "#053061",
            "#2166ac",
            "#4393c3",
            "#92c5de",
            "#d1e5f0",
            "#f7f7f7",
            "#fddbc7",
            "#f4a582",
            "#d6604d",
            "#b2182b",
            "#67001f",
        ]
        matrix = self.matrix
        min_value = np.min(matrix)
        max_value = np.max(matrix)
        for row in range(self.rowCount()):
            for col in range(self.columnCount()):
                value = matrix[row, col]
                index = int(
                    (value - min_value) / (max_value - min_value) * (len(colors) - 1)
                )
                color = QColor(colors[index])
                self.set_item_color(row, col, color)
        self.blockSignals(False)

    def _value_to_string(self, value: Union[str, float, int]) -> str:
        if isinstance(value, float):
            return f"{value:.{self._precision}f}"
        return f"{value}"

    def _value_from_string(self, value: str) -> Union[str, float, int]:
        if re.match("^[+-]?\\d+$", value):
            return int(value)
        elif re.match(r"^[+-]?\d+(\.\d+)?$", str(value)):
            return float(value)
        return value

    @property
    def horizontal_header(self) -> List[str]:
        return [self.horizontalHeaderItem(i).text() for i in range(self.columnCount())]

    @horizontal_header.setter
    def horizontal_header(self, header: List[str]):
        self.setColumnCount(len(header))
        for i, text in enumerate(header):
            self.setHorizontalHeaderItem(i, QTableWidgetItem(text))
        self.horizontalHeader().show()

    @property
    def vertical_header(self) -> List[str]:
        return [self.verticalHeaderItem(i).text() for i in range(self.rowCount())]

    @vertical_header.setter
    def vertical_header(self, header: List[str]):
        self.setRowCount(len(header))
        for i, text in enumerate(header):
            self.setVerticalHeaderItem(i, QTableWidgetItem(text))
        self.verticalHeader().show()

    @property
    def precision(self) -> int:
        return self._precision

    @precision.setter
    def precision(self, precision: int):
        self._precision = precision
        # refresh matrix
        self.matrix = self.matrix

    def item_color(self, row: int, col: int) -> QColor:
        return self.item(row, col).background().color()

    def set_item_color(self, row: int, col: int, color: QColor):
        self.item(row, col).setBackground(color)

    def column_color(self, col: int) -> QColor:
        # return color of the last item in the column
        return self.item_color(self.rowCount() - 1, col)

    def set_column_color(self, col: int, color: QColor):
        for row in range(self.rowCount()):
            self.set_item_color(row, col, color)

    def row_color(self, row: int) -> QColor:
        # return color of the last item in the row
        return self.item_color(row, self.columnCount() - 1)

    def set_row_color(self, row: int, color: QColor):
        for col in range(self.columnCount()):
            self.set_item_color(row, col, color)
