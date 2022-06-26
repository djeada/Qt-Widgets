from PyQt6 import QtCore
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor, QPen, QPainter, QFontMetrics
from PyQt6.QtWidgets import QComboBox


class ToggleButton(QComboBox):
    '''
    Toogle button is a QComboBox with a custom paint event.
    '''
    def __init__(self, parent=None):
        super().__init__(parent)
    
    def paintEvent(self, event):
        n = self.count()
        if n == 0:
            return
        for i in range(n):
            text = self.itemText(i)
            rect = self._ith_rectangle(i)
            background_color = QColor("white") if i != self.currentIndex() else QColor("#4682B4")
            foreground_color = QColor("#4682B4") if i != self.currentIndex() else QColor("white")
            self._paint_button(rect, foreground_color, background_color, text)

    def mousePressEvent(self, event):
        for i in range(self.count()):
            rect = self._ith_rectangle(i)
            if rect.contains(event.pos()):
                self.setCurrentIndex(i)
                self.activated.emit(i)
                return
        super().mousePressEvent(event)

    def sizeHint(self):
        # must fit all the buttons and their text
        total_width = 0

        for i in range(self.count()):
            text = self.itemText(i)
            metrics = QFontMetrics(self.font())
            rect = metrics.boundingRect(text)
            total_width += rect.width()*1.5

        width = total_width if total_width > self.rect().width() else self.rect().width()
        height = self.rect().height()

        return QtCore.QSize(width, height)

    def _paint_button(self, rect, foreground_color, background_color, text):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        painter.setPen(QPen(background_color))
        painter.setBrush(background_color)
        painter.drawRoundedRect(rect, 0, 0)
        painter.setPen(QPen(foreground_color))
        painter.drawText(rect,  Qt.AlignmentFlag.AlignCenter, text)
        painter.end()

    def _ith_rectangle(self, i):
        start_x = self.rect().x()
        start_y = self.rect().y()
        width = self.rect().width()//self.count()
        height = self.rect().height()
        return QtCore.QRect(start_x + i*width, start_y, width, height)
    