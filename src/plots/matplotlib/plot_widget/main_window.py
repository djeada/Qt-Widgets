from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import QDir
import numpy as np


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        x_points = np.linspace(0, 10, 100)
        y_points = np.sin(x_points)
        self.plot_widget.plot(x_points, y_points, "x", "y", "sin(x)")
        self.show()