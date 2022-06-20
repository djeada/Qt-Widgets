from PyQt6 import QtGui
from PyQt6.QtCore import QRectF, QObject, Qt
from PyQt6.QtGui import QPen, QColor
from PyQt6.QtWidgets import QGraphicsItem

rect_size = 100

class MovableImage(
    QGraphicsItem, QObject):
    def __init__(self, parent=None):
        super(QGraphicsItem, self).__init__()
        #super(QObject, self).__init__(parent)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemSendsScenePositionChanges)
    
    def boundingRect(self):
        return QRectF(-rect_size / 2, -rect_size / 2, rect_size, rect_size)

    def paint(self, painter, option, widget):
        brush_color = self.isSelected() and QtGui.QColorConstants.DarkGreen or QtGui.QColorConstants.DarkGray
        painter.setPen(QPen(QColor("black")))
        painter.setBrush(brush_color)
        painter.drawRect(-rect_size / 2, -rect_size / 2, rect_size, rect_size)
