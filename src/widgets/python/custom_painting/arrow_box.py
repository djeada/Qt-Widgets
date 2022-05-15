from PyQt6 import QtWidgets, QtGui, QtCore
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor, QPen, QPainter, QPolygonF


class ArrowBox(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

    def sizeHint(self):
        if self.width() < 20 or self.height() < 20:
            return QtCore.QSize(20, 20)
        return QtCore.QSize(self.width(), self.height())

    def paintEvent(self, e):
        painter = QPainter(self)
        painter.setRenderHints(
            QtGui.QPainter.RenderHint.Antialiasing
            | QtGui.QPainter.RenderHint.TextAntialiasing
        )

        pen = QPen(QColor("black"))
        pen.setWidth(0.1 * self.width())
        painter.setPen(pen)
        painter.drawLine(self.width() / 2, 0, self.width() / 2, 0.8 * self.height())
        pen.setWidth(1)
        painter.setBrush(QColor("black"))
        painter.drawPolygon(
            QPolygonF()
            << QtCore.QPointF(self.width() / 2, self.height())
            << QtCore.QPointF(
                self.width() / 2 - 0.2 * self.width(), 0.8 * self.height()
            )
            << QtCore.QPointF(
                self.width() / 2 + 0.2 * self.width(), 0.8 * self.height()
            )
        )
