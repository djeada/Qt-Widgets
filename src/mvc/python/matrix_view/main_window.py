import numpy as np
from PyQt6 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        # 2d matrix of floats
        matrix = np.random.rand(10, 10)
        self.tableWidget.matrix = matrix
        self.tableWidget.horizontal_header = [
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
        ]
        self.colored_cells.toggled.connect(
            lambda flag: setattr(self.tableWidget, "colored_cells", flag)
        )
        self.format_input.textChanged.connect(
            lambda text: setattr(self.tableWidget, "precision", int(text))
        )

        self.show()
