from PyQt6.QtCore import Qt, QSize
from PyQt6.QtGui import QIcon, QColor, QPen
from PyQt6.QtWidgets import QStyledItemDelegate


class CryptoRankingDelegate(QStyledItemDelegate):
    def __init__(self, parent=None):
        super(CryptoRankingDelegate, self).__init__(parent)

    def paint(self, painter, option, index):
        column = index.column()

        if column == 2:
            value = index.data()
            oldPen = painter.pen()
            if value < 0:
                painter.setPen(QPen(QColor("#8b0000")))
            else:
                painter.setPen(QPen(QColor("#006600")))
            icon = index.data(Qt.ItemDataRole.DecorationRole)
            pixmap = icon.pixmap(option.decorationSize)
            painter.drawPixmap(option.rect.x() + 1, option.rect.y() + option.rect.height() / 2 - pixmap.height() / 2, pixmap)
            painter.drawText(option.rect,
                            Qt.AlignmentFlag.AlignCenter,
                         f"{value:.0f}%")
            painter.setPen(oldPen)
        elif column == 1 or column == 3 or column == 4:
            value = index.data()
            rect = option.rect
            rect.setX(rect.x() + 3)
            painter.drawText(rect,
                            option.displayAlignment,
                           f"${value:.0f}%")
        else:
            super().paint(painter, option, index)
    
    def sizeHint(self, option, index):
        originalSize = QStyledItemDelegate.sizeHint(self, option, index)
        return QSize(originalSize.width(), originalSize.height() * 2)
    

