from PyQt6 import QtWidgets, uic
import sys

from PyQt6.QtCore import pyqtSlot, pyqtSignal


class MainWindow(QtWidgets.QMainWindow):

    send_string = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        uic.loadUi('main_window.ui', self)

        self.pushButton.clicked.connect(lambda : self.send_string.emit(self.lineEdit.text()))
        self.send_string.connect(lambda message: self.slot_display_string(message))
        self.show()

    @pyqtSlot()
    def slot_display_string(self, message):
        self.label.setText(message)


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    app.exec()


if __name__ == '__main__':
    main()
