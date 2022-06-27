from PyQt6.QtCore import Qt, QSize, QPointF
from PyQt6.QtGui import QPen, QColor, QLinearGradient
from PyQt6.QtWidgets import QStyledItemDelegate, QStyle


class EmojiPickerDelegate(QStyledItemDelegate):
    def __init__(self, parent=None):
        super().__init__(parent)

    def paint(self, painter, option, index):
        rect = option.rect
        # make the rect to be square
        rect.setWidth(rect.height())
        icon = index.data(Qt.ItemDataRole.DecorationRole)
        if icon:
            # check if item is hovered
            if option.state & QStyle.StateFlag.State_MouseOver:
                painter.save()
                gradient = QLinearGradient(
                    QPointF(rect.topLeft()), QPointF(rect.bottomLeft())
                )
                gradient.setColorAt(0, QColor(0, 0, 255, 50))
                gradient.setColorAt(1, QColor(0, 0, 255, 50))
                painter.fillRect(rect, gradient)
                painter.restore()
            # draw icon as pixmap at the center of the option rect
            pixmap_rect = rect
            pixmap_rect.setWidth(rect.width() * 0.8)
            pixmap_rect.setHeight(rect.height() * 0.8)
            pixmap_rect.moveCenter(rect.center())
            pixmap = icon.pixmap(pixmap_rect.size())
            painter.drawPixmap(pixmap_rect, pixmap)
        else:
            # remove selection from option
            option_copy = option
            option_copy.state = QStyle.StateFlag.State_Enabled
            super().paint(painter, option_copy, index)

    def sizeHint(self, option, index):
        original_size = QStyledItemDelegate.sizeHint(self, option, index)
        return QSize(original_size.width(), original_size.height() * 2)
