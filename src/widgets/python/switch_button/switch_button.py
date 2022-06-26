from PyQt6 import QtCore
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor, QPen, QPainter, QFontMetrics
from PyQt6.QtWidgets import QCheckBox


class SwitchButton(QCheckBox):
    '''
    Toogle button is a QCheckBox with a custom paint event.
    '''
    def __init__(self, parent=None):
        super().__init__(parent)
    
    def paintEvent(self, event):
        # background green rounded rectangle
        # on top of it white circle on left if unchecked or right if checked

        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        painter.setPen(QPen(QColor("#4682B4")))
        painter.setBrush(QColor("#4682B4"))
        painter.drawRoundedRect(self.rect(), 0, 0)
        painter.setPen(QPen(QColor("white")))
        painter.setBrush(QColor("white"))
        painter.drawEllipse(self.rect().x() + self.rect().width()/2 - self.rect().height()/2,
                            self.rect().y(),
                            self.rect().height(),
                            self.rect().height())
        if self.isChecked():
            painter.drawEllipse(self.rect().x() + self.rect().width()/2 - self.rect().height()/2,
                                self.rect().y(),
                                self.rect().height(),
                                self.rect().height())
        painter.end()

    def mousePressEvent(self, event):
        self.setChecked(not self.isChecked())
        self.clicked.emit(self.isChecked())
        super().mousePressEvent(event)
