from PyQt6 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.toggleButtonA.addItems(["A", "B", "C"])
        self.toggleButtonB.addItem("Single")
        self.toggleButtonC.addItems(["Tree View", "Map View"])

        self.show()
