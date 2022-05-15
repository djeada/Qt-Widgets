from PyQt6 import QtWidgets, uic
from PyQt6.QtWidgets import QMessageBox
import sys


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.pushButton.released.connect(self.show_message_box)
        self.show()

    def show_message_box(self):
        message_box = QMessageBox()
        message_box.setIcon(QMessageBox.Icon.Warning)
        message_box.setWindowTitle("My Application")
        message_box.setText(
            "The most recent modifications are not saved.\nWould you like to save them?"
        )
        message_box.setStandardButtons(
            QMessageBox.StandardButton.Save
            | QMessageBox.StandardButton.Discard
            | QMessageBox.StandardButton.Cancel
        )
        message_box.setDefaultButton(QtWidgets.QMessageBox.StandardButton.Save)
        result = message_box.exec()

        if result == QtWidgets.QMessageBox.StandardButton.Save:
            QtWidgets.QMessageBox.information(
                None, "My Application", "Save clicked."
            ).show()
        elif result == QtWidgets.QMessageBox.StandardButton.Discard:
            QtWidgets.QMessageBox.information(
                None, "My Application", "Discard clicked."
            ).show()
        elif result == QtWidgets.QMessageBox.StandardButton.Cancel:
            QtWidgets.QMessageBox.information(
                None, "My Application", "Cancel clicked."
            ).show()
        else:
            pass


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
