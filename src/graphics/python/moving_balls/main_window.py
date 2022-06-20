from PyQt6 import QtWidgets, uic, QtGui, QtCore
from PyQt6.QtCore import QRectF, QObject

from bordered_scene import BorderedScene
from movable_image import MovableImage


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.scene = BorderedScene(QRectF(0, 0, 300, 300), 10, self)
        self.graphicsView.setScene(self.scene)

        timer = QtCore.QTimer(self)
        timer.timeout.connect(self.scene.advance)
        timer.start(100)

        self.show()

    def on_addButton_released(self):
        self.scene.addItem(MovableImage(self.scene.sceneRect(), self))

    def on_removeButton_released(self):
        for item in self.scene.selectedItems():
            self.scene.removeItem(item)
            del item
