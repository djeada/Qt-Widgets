import sys

from main_window import MainWindow
from PyQt6 import QtWidgets


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
