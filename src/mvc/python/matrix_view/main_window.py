import numpy as np
from PyQt6 import QtWidgets, uic
from PyQt6.QtGui import QColor


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        # 2d matrix of floats
        matrix = np.random.rand(10, 10)
        self.tableWidget.matrix = matrix
        self.tableWidget.horizontal_header = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]

        # 1d matrix of floats
        matrix = np.array([1, 2, 3, 4, 5, 6]).T
        self.tableWidget.matrix = matrix
        #self.tableWidget.horizontal_header = ["A", "B", "C", "D", "E", "F"]

        # 1d matrix of strings
        #matrix = np.array(["A", "B", "C", "D", "E", "F"]).T
        #self.tableWidget.matrix = matrix
        #self.tableWidget.horizontal_header = ["A", "B", "C", "D", "E", "F"]

        self.show()

