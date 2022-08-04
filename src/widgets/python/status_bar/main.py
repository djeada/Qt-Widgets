import sys

from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import pyqtSlot


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        # connect reset button released with progressBar
        self.resetButton.clicked.connect(self.slot_resetButton)

        # when stop button is checked, start button is unchecked
        # and vice versa
        self.stopButton.toggled.connect(lambda flag: self.slot_stopButton(flag))

        self.startButton.toggled.connect(lambda flag: self.slot_startButton(flag))

        self.show()

    @pyqtSlot()
    def slot_resetButton(self):
        print("rest")
        self.progressBar.setValue(0)

    @pyqtSlot()
    def slot_stopButton(self, flag):
        self.startButton.setChecked(not flag)
        if flag:
            self.progressBar.stop()

    @pyqtSlot()
    def slot_startButton(self, flag):
        self.stopButton.setChecked(not flag)
        if flag:
            self.progressBar.start()


def main():
    app = QtWidgets.QApplication(sys.argv)
    MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
