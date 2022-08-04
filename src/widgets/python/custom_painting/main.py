import sys

from PyQt6 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.show()


def main():
    app = QtWidgets.QApplication(sys.argv)
    MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
