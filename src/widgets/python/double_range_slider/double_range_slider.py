from PyQt6 import QtCore
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor, QPen, QPainter, QFontMetrics
from PyQt6.QtWidgets import QSlider


class DoubleRangeSlider(QSlider):
    """
    Slider with two handles.
    """

    minValueChanged = QtCore.pyqtSignal(int)
    maxValueChanged = QtCore.pyqtSignal(int)

    def __init__(self, parent=None):
        super().__init__(parent)
        self._left_handle = 0 # left handle position
        self._right_handle = 0 # right handle position

    @property
    def minValue(self):
        """
        Get the minimum value.
        """
        return self._left_handle
    
    @minValue.setter
    def minValue(self, value):
        """
        Set the minimum value.
        """
        self._left_handle = value
        self.update()
        self.minValueChanged.emit(value)

    @maxValue.setter
    def maxValue(self, value):
        """
        Set the maximum value.
        """
        self._right_handle = value
        self.update()
        self.maxValueChanged.emit(value)

    def paintEvent(self, event):
        """
        Paint the slider.
        """
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)
        painter.setPen(QPen(Qt.black, 1, Qt.SolidLine))
        painter.setBrush(Qt.NoBrush)
        painter.drawRect(self.rect())

        # draw the handles
        painter.setBrush(Qt.red)
        painter.drawEllipse(self._left_handle - 5, self.height() / 2 - 5, 10, 10)
        painter.setBrush(Qt.blue)
        painter.drawEllipse(self._right_handle - 5, self.height() / 2 - 5, 10, 10)

        # draw the labels
        painter.setFont(self.font())
        painter.setPen(Qt.black)
        painter.drawText(self._left_handle, self.height() / 2 + QFontMetrics(self.font()).height() / 2, str(self.minimum()))
        painter.drawText(self._right_handle, self.height() / 2 + QFontMetrics(self.font()).height() / 2, str(self.maximum()))

        # draw the line
        painter.setPen(QPen(Qt.black, 1, Qt.SolidLine))
        painter.drawLine(self._left_handle, self.height() / 2, self._right_handle, self.height() / 2)

        # draw the range
        painter.setPen(QPen(Qt.black, 1, Qt.DotLine))
        painter.drawLine(self._left_handle, self.height() / 2, self._right_handle, self.height() / 2)

    
    def mousePressEvent(self, event):
        """
        Handle mouse press events.
        """
        if event.button() == Qt.LeftButton:
            if event.x() < self._left_handle:
                self.setValue(self.minimum())
            elif event.x() > self._right_handle:
                self.setValue(self.maximum())
            else:
                self.setValue(event.x())
            self.update()
            self.emit(QtCore.SIGNAL('valueChanged(int)'), self.value())
    
    def mouseMoveEvent(self, event):
        """
        Handle mouse move events.
        """
        if event.buttons() & Qt.LeftButton:
            if event.x() < self._left_handle:
                self.setValue(self.minimum())
            elif event.x() > self._right_handle:
                self.setValue(self.maximum())
            else:
                self.setValue(event.x())
            self.update()
            self.emit(QtCore.SIGNAL('valueChanged(int)'), self.value())
        
    def mouseReleaseEvent(self, event):
        """
        Handle mouse release events.
        """
        self.update()
        self.emit(QtCore.SIGNAL('valueChanged(int)'), self.value())
