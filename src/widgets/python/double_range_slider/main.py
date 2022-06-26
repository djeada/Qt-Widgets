from PyQt6 import QtWidgets
import sys

from main_window import MainWindow


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
