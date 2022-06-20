from PyQt6 import QtWidgets, uic, QtGui
from PyQt6.QtCore import Qt, QRectF
from PyQt6.QtGui import QPixmap, QPen, QColor
from PyQt6.QtWidgets import QMessageBox


class ImageCropper(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(ImageCropper, self).__init__(parent)
        self.setAcceptDrops(True)
        self.pixmap = QPixmap()

    def paintEvent(self, event):
        painter = QtGui.QPainter()
        painter.begin(self)
        painter.setPen(QPen(QColor("black")))
        painter.setBrush(Qt.BrushStyle.NoBrush)
        painter.drawEllipse(self.rect().center(), self.rect().width() / 2, self.rect().height() / 2)
        painter.end()
        if self.pixmap.isNull():
            painter.begin(self)
            painter.setPen(QPen(QColor("black")))
            painter.setBrush(Qt.BrushStyle.NoBrush)
            painter.drawText(self.rect(), Qt.AlignmentFlag.AlignCenter, "Drag and drop an image here")
            painter.end()
        else:
            painter.begin(self)
            path = QtGui.QPainterPath()
            path.addEllipse(QRectF(self.rect()))
            painter.setClipPath(path)
            painter.drawPixmap(self.rect(), self.pixmap)
            painter.end()
    
    def dropEvent(self, event):
        urls = event.mimeData().urls()
        if len(urls) == 0:
            return
        file_name = urls[0].toLocalFile()
        self.set_pixmap_from_file(file_name)
    
    def set_pixmap_from_file(self, file_name):
        new_pix = QtGui.QPixmap(file_name)
        if new_pix.isNull():
            QMessageBox.warning(self, "Invalid Image",
                                 "You tried loading an invalid file.")
            return
        self.pixmap = new_pix
        self.update()

    def dragEnterEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()
    
    def dragMoveEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()
    