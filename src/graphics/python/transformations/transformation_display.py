from PyQt6.QtCore import QPoint, Qt, QSize
from PyQt6.QtGui import QPixmap, QPainter, QFont
from PyQt6.QtWidgets import QWidget


class TransformationDisplay(QWidget):
    def __init__(self, parent=None):
        super(TransformationDisplay, self).__init__(parent)
        self._translation = QPoint(0, 0)
        self._rotation = 0
        self._scale = 1
        self.pixmap = QPixmap()

    @property
    def translate(self):
        return self._translation

    @translate.setter
    def translate(self, point):
        self._translation = point
        self.update()

    def update_translate(self, point):
        self.translate = point

    @property
    def scale(self):
        return self._scale

    @scale.setter
    def scale(self, scale):
        self._scale = scale
        self.update()

    def update_scale(self, scale):
        self.scale = scale

    @property
    def rotate(self):
        return self._rotation

    @rotate.setter
    def rotate(self, angle):
        self._rotation = angle
        self.update()

    def update_rotate(self, angle):
        self.rotate = angle

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.translate(self._translation)
        painter.rotate(self._rotation)
        painter.scale(self._scale, self._scale)

        # set font size to height of widget / 3
        painter.setFont(QFont("Arial", self.height() / 3))

        # Draw Qt text in the center of the widget
        # Make sure the whole text is visible
        painter.drawText(self.rect(), Qt.AlignmentFlag.AlignCenter, "Qt")

    def sizeHint(self):
        if self.width() < 20 or self.height() < 20:
            return QSize(20, 20)
        return QSize(self.width(), self.height())
