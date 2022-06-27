from random import randint, uniform

from PyQt6.QtCore import QPointF, QRectF, QObject, QPoint
from PyQt6.QtGui import QBrush, QPen, QColor, QPainter
from PyQt6.QtWidgets import QGraphicsItem

rectSize = 30


class MovableImage(QGraphicsItem, QObject):
    def __init__(self, rectBorder, parent=None):
        super(QGraphicsItem, self).__init__()
        # super(QObject, self).__init__(parent)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable)
        self.speed = self.randomize_speed()
        start_x = (randint(0, rectBorder.width() - rectSize)) + rectBorder.x()
        start_y = (randint(0, rectBorder.height() - rectSize)) + rectBorder.y()
        self.setPos(start_x, start_y)

    def boundingRect(self):
        return QRectF(-rectSize / 2, -rectSize / 2, rectSize, rectSize)

    def paint(self, painter, option, widget):
        painter.setRenderHint(QPainter.RenderHint.SmoothPixmapTransform)
        rect = self.boundingRect()

        if len(self.scene().collidingItems(self)) > 0:
            pen = QPen(QColor("red"))
            painter.setPen(pen)
            brush = QBrush(QColor("red"))
            self.collide_wall()
        else:
            pen = QPen(QColor("green"))
            brush = QBrush(QColor("green"))
            painter.setPen(pen)
        painter.setBrush(brush)
        painter.drawEllipse(rect)

    def advance(self, phase):
        self.setPos(self.x() + self.speed.x(), self.y() + self.speed.y())

    def collide_wall(self):
        x = self.pos().x()
        y = self.pos().y()
        scene_rect = self.scene().sceneRect()
        left_wall = scene_rect.x()
        right_wall = scene_rect.x() + scene_rect.width()
        top_wall = scene_rect.y()
        bottom_wall = scene_rect.y() + scene_rect.height()
        if x - self.boundingRect().width() <= left_wall:
            self.speed = QPointF(abs(self.speed.x()), self.speed.y())
            x = left_wall + self.boundingRect().width()
        if x + self.boundingRect().width() >= right_wall:
            self.speed = QPointF(-abs(self.speed.x()), self.speed.y())
            x = right_wall - self.boundingRect().width()
        if y - self.boundingRect().height() <= top_wall:
            self.speed = QPointF(self.speed.x(), abs(self.speed.y()))
            y = top_wall + self.boundingRect().height()
        if y + self.boundingRect().height() >= bottom_wall:
            self.speed = QPointF(self.speed.x(), -abs(self.speed.y()))
            y = bottom_wall - self.boundingRect().height()
        self.setPos(x, y)

    def randomize_speed(self):
        speed_x = uniform(-5, 5)
        speed_y = uniform(-5, 5)
        self.speed = QPointF(speed_x, speed_y)
        return self.speed

    def reverse_speed(self):
        self.speed = QPointF(-self.speed.x(), -self.speed.y())

    def speed_direction(self):
        try:
            x_dir = self.speed.x() // abs(self.speed.x())
            y_dir = self.speed.y() // abs(self.speed.y())
        except ZeroDivisionError:
            self.randomize_speed()
            return self.speed_direction()

        return QPoint(x_dir, y_dir)
