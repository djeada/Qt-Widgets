from PyQt6 import QtWidgets, uic
import sys


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)

        self.label_1.setToolTip(
            '<html><head/><body><p><span style=" font-size:10pt; '
            'font-weight:600;">Custom tooltip</span></p></body></html>'
        )
        self.label_2.setToolTip(
            '<html><head/><body><p><span style=" font-size:10pt; '
            'font-weight:600;">Custom tooltip</span></p><p><span style=" '
            'font-size:10pt; font-weight:600;">with bullet list <ol> <li>item '
            "1</li> <li>item 2</li> <li>item 3</li> </ol></span></p></body></html>"
        )
        self.label_3.setToolTip(
            '<html><head/><body><p><span style=" font-size:10pt; '
            'font-weight:600;">Custom tooltip</span></p><p><span style=" '
            'font-size:10pt; font-weight:600;">with image <img '
            'src="https://placekitten.com/200/300"/></span></p></body></html>'
        )

        self.show()


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    app.exec()


if __name__ == "__main__":
    main()
