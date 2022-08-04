from PyQt6 import QtCore
from PyQt6.QtGui import QPainter, QPen
from PyQt6.QtWidgets import QCheckBox


class SwitchButton(QCheckBox):
    """
    Switch button is a QCheckBox with a custom paint event.
    """

    def __init__(self, parent=None):
        super().__init__(parent)

    def paintEvent(self, event):

        rect_height = 0.9 * self.rect().height()
        circle_radius = 1.1 * rect_height
        rect_width = 2 * 0.9 * circle_radius

        offset = self.rect().width() - 2 * 0.9 * circle_radius
        x_rect = self.rect().x() + offset / 2
        y_rect = self.rect().y() + 0.05 * rect_height

        x_circle = x_rect - 0.05 * rect_width
        y_circle = y_rect - 0.045 * rect_height

        if not self.isChecked():
            x_circle += circle_radius

        foreground_color = self.palette().light().color()
        background_color = (
            self.palette().dark().color()
            if self.isChecked()
            else self.palette().highlight().color()
        )

        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        painter.setPen(QPen(background_color))
        painter.setBrush(background_color)
        painter.drawRoundedRect(
            x_rect,
            y_rect,
            rect_width,
            rect_height,
            0.5 * rect_height,
            0.5 * rect_height,
        )
        painter.setPen(QPen(foreground_color))
        painter.setBrush(foreground_color)
        painter.drawEllipse(x_circle, y_circle, circle_radius, circle_radius)
        painter.end()

    def mousePressEvent(self, event):
        self.setChecked(not self.isChecked())
        self.clicked.emit(self.isChecked())
        super().mousePressEvent(event)

    def sizeHint(self):
        return QtCore.QSize(self.rect().width() * 5, self.rect().height() * 5)
