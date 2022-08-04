from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QColor, QPainter, QPen, QPixmap
from PyQt6.QtWidgets import (
    QDialog,
    QLineEdit,
    QProgressBar,
    QSlider,
    QStyledItemDelegate,
    QVBoxLayout,
)


class CustomDelegate(QStyledItemDelegate):
    def __init__(self, parent=None):
        super().__init__(parent)

    def paint(self, painter, option, index):
        row = index.row()

        if row == 1:
            # create QProgressBar
            progress_bar = QProgressBar()
            progress_bar.setGeometry(option.rect)
            progress_bar.setValue(int(index.data()))
            progress_bar.setTextVisible(False)
            progress_bar.setStyleSheet(
                "QProgressBar::chunk { background-color: #006400; }"
            )
            pixmap = QPixmap(option.rect.size())
            progress_bar.render(pixmap)
            painter.drawPixmap(option.rect, pixmap)
        elif row == 3:
            old_pen = painter.pen()
            pen = QPen(
                QColor("#FFD700"),
                1,
                Qt.PenStyle.DashLine,
                Qt.PenCapStyle.RoundCap,
                Qt.PenJoinStyle.RoundJoin,
            )
            painter.setPen(pen)
            painter.setBrush(QColor("#FFD700"))
            painter.setRenderHint(QPainter.RenderHint.Antialiasing)

            painter.drawRect(
                option.rect.center().x() - 30, option.rect.center().y() - 10, 20, 20
            )
            painter.drawRect(
                option.rect.center().x() + 10, option.rect.center().y() - 10, 20, 20
            )
            painter.setPen(old_pen)
        else:
            # draw background blue
            painter.fillRect(option.rect, QColor(176, 224, 230))
            # center text
            text = index.data()
            rect = option.rect
            text_rect = painter.boundingRect(rect, Qt.AlignmentFlag.AlignCenter, text)
            text_rect.moveCenter(rect.center())
            painter.drawText(text_rect, Qt.AlignmentFlag.AlignCenter, text)

    def sizeHint(self, option, index):
        # make it twice as long as the default
        original_size = QStyledItemDelegate.sizeHint(self, option, index)
        return QSize(original_size.width(), original_size.height() * 2)

    def createEditor(self, parent, option, index):
        row = index.row()
        if row == 1:
            dialog = QDialog(parent)
            dialog.setWindowFlags(Qt.WindowType.Popup)
            slider = QSlider(Qt.Orientation.Horizontal)
            slider.setRange(0, 100)
            slider.setValue(int(index.data()))
            slider.setTickPosition(QSlider.TickPosition.TicksBothSides)
            slider.setTickInterval(10)
            dialog.setLayout(QVBoxLayout())
            dialog.layout().addWidget(slider)
            return dialog
        elif row == 3:
            return None
        else:
            editor = QLineEdit(parent)
            editor.setText(index.data())
            return editor

    def setModelData(self, editor, model, index):
        row = index.row()
        if row == 1:
            dialog = editor
            slider = dialog.findChild(QSlider)
            model.setData(index, slider.value())
        else:
            line_edit = editor
            model.setData(index, line_edit.text())
