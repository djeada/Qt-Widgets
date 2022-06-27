from PyQt6 import QtWidgets, uic, QtGui
from PyQt6.QtCore import QPoint


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        self.xSpinBox.setValue(self.transformationDisplay.translate.x())
        self.ySpinBox.setValue(self.transformationDisplay.translate.y())
        self.scaleSpinBox.setValue(self.transformationDisplay.scale * 100)
        self.rotateSpinBox.setValue(self.transformationDisplay.rotate)

        # connect ui->transformationDisplay setTranslate() to xSpinBox and ySpinBox
        self.xSpinBox.valueChanged.connect(
            lambda x: self.transformationDisplay.update_translate(
                QPoint(x, self.transformationDisplay.translate.y())
            )
        )
        self.ySpinBox.valueChanged.connect(
            lambda y: self.transformationDisplay.update_translate(
                QPoint(self.transformationDisplay.translate.x(), y)
            )
        )
        self.scaleSpinBox.valueChanged.connect(
            lambda scale: self.transformationDisplay.update_scale(scale / 100)
        )
        self.rotateSpinBox.valueChanged.connect(
            lambda angle: self.transformationDisplay.update_rotate(angle)
        )

        self.show()
