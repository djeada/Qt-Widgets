from dataclasses import dataclass
from enum import Enum, auto

from PyQt6 import QtCore
from PyQt6.QtCore import Qt, QRect
from PyQt6.QtGui import QPainter
from PyQt6.QtWidgets import QSlider, QStyle, QStyleOptionSlider, QApplication

HANDLE_WIDTH = 5


class LastSate(Enum):
    NONE = auto()
    LEFT = auto()
    RIGHT = auto()


@dataclass
class ValueRange:
    min: float
    max: float


class DoubleRangeSlider(QSlider):
    """
    Slider with two handles.
    """

    value_changed = QtCore.pyqtSignal(ValueRange)

    def __init__(self, parent=None):
        super().__init__(parent)
        self._left_handle = 0  # left handle position
        self._right_handle = 100  # right handle position
        self._last_state = LastSate.NONE  # which handle is currently hovered
        self.setMouseTracking(True)

    @property
    def min_value(self):
        """
        Get the minimum value.
        """
        return self._left_handle

    @min_value.setter
    def min_value(self, value):
        """
        Set the minimum value.
        """
        if value < 0:
            value = 0
        if value + HANDLE_WIDTH // 2 > self._right_handle:
            value = self._right_handle - HANDLE_WIDTH // 2
        self._left_handle = value
        self.update()
        self.value_changed.emit(ValueRange(self.min_value, self.max_value))

    @property
    def max_value(self):
        """
        Get the maximum value.
        """
        return self._right_handle

    @max_value.setter
    def max_value(self, value):
        """
        Set the maximum value.
        """
        if value > 100:
            value = 100
        if value < self._left_handle + HANDLE_WIDTH // 2:
            value = self._left_handle + HANDLE_WIDTH // 2
        self._right_handle = value
        self.update()
        self.value_changed.emit(ValueRange(self.min_value, self.max_value))

    def paintEvent(self, event):
        """
        Paint the slider.
        """
        painter = QPainter(self)
        style = QApplication.style()
        option = QStyleOptionSlider()
        option.initFrom(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        position_range = self.width() - HANDLE_WIDTH * 2

        # Draw the groove.
        option.subControls = QStyle.SubControl.SC_SliderGroove
        option.orientation = self.orientation()
        option.state = QStyle.StateFlag.State_Enabled
        style.drawComplexControl(QStyle.ComplexControl.CC_Slider, option, painter, self)

        # Draw the handles.
        option.subControls = QStyle.SubControl.SC_SliderHandle

        # Draw the left handle.
        x = self._left_handle * position_range / 100
        self._draw_handle(option, painter, style, x, LastSate.LEFT)

        # Draw the right handle.
        x = self._right_handle * position_range / 100
        self._draw_handle(option, painter, style, x, LastSate.RIGHT)

        painter.end()

    def _draw_handle(self, option, painter, style, x, state):
        if self.orientation() == Qt.Orientation.Horizontal:
            option.rect = QRect(x, 0, HANDLE_WIDTH, self.height())
        else:
            option.rect = QRect(0, x, self.width(), HANDLE_WIDTH)

        # change handle color if mouse hover
        if self._last_state == state:
            if QApplication.mouseButtons() == Qt.MouseButton.LeftButton:
                option.state = QStyle.StateFlag.State_Off
            else:
                option.state = (
                    QStyle.StateFlag.State_Enabled | QStyle.StateFlag.State_MouseOver
                )
                option.activeSubControls = QStyle.SubControl.SC_SliderHandle
        else:
            option.activeSubControls = QStyle.SubControl.SC_None
            option.state = QStyle.StateFlag.State_Enabled

        style.drawComplexControl(QStyle.ComplexControl.CC_Slider, option, painter, self)

    def mousePressEvent(self, event):
        """
        Handle mouse press events.
        """
        if event.button() != Qt.MouseButton.LeftButton:
            return

        left_position = self._value_to_pixels(self._left_handle)
        right_position = self._value_to_pixels(self._right_handle)
        event_pos = event.pos().x()

        if event_pos < left_position or abs(event_pos - left_position) < abs(
            event_pos - right_position
        ):
            self.min_value = self._pixels_to_value(event_pos)
        else:
            self.max_value = self._pixels_to_value(event_pos)
            self._last_state = LastSate.RIGHT

    def mouseMoveEvent(self, event):
        """
        Handle mouse move events.
        """

        left_position = self._value_to_pixels(self._left_handle)
        right_position = self._value_to_pixels(self._right_handle)
        event_pos = event.pos().x()
        dist_left = abs(event_pos - left_position)
        dist_right = abs(event_pos - right_position)

        if event_pos < left_position or dist_left < dist_right:
            self._last_state = (
                LastSate.LEFT if dist_left <= HANDLE_WIDTH else LastSate.NONE
            )
            if event.buttons() == Qt.MouseButton.LeftButton:
                self.min_value = self._pixels_to_value(event_pos)
        else:
            self._last_state = (
                LastSate.RIGHT if dist_right <= HANDLE_WIDTH else LastSate.NONE
            )
            if event.buttons() == Qt.MouseButton.LeftButton:
                self.max_value = self._pixels_to_value(event_pos)
        self.update()

    def mouseReleaseEvent(self, event):
        """
        Handle mouse release events.
        """
        self.update()

    def leaveEvent(self, event):
        """
        Handle focus out events.
        """
        self._last_state = LastSate.NONE
        self.update()

    def _pixels_to_value(self, pixels):
        """
        Convert pixels to a value.
        """
        return pixels * 100 / self.width()

    def _value_to_pixels(self, value):
        """
        Convert a value to pixels.
        """
        return value * self.width() / 100
