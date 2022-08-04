from movable_image import MovableImage
from PyQt6 import QtGui, QtWidgets, uic
from PyQt6.QtWidgets import QGraphicsItem


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.scene = QtWidgets.QGraphicsScene(self)
        self.graphicsView.setScene(self.scene)
        text = self.scene.addText("Drop pictures here", QtGui.QFont("Ubuntu", 20))
        text.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        text.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable)
        self.show()

    def on_addButton_released(self):
        new_item = MovableImage(self)
        self.scene.addItem(new_item)

    def on_removeButton_released(self):
        for item in self.scene.selectedItems():
            self.scene.removeItem(item)
            del item
