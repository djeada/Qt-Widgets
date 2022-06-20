from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import QDir


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.show()

    def on_actionSave_triggered(self):
        pass

    def on_actionOpen_triggered(self):
        file_name = QtWidgets.QFileDialog.getOpenFileName(
            self, "Open Image", QDir.currentPath(),
            "Image Files (*.jpg *.JPG *.png *.PNG, *.bmp, *.BMP)"
        )
        self.image_cropper.set_pixmap_from_file(file_name)
