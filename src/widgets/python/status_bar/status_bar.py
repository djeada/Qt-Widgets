from PyQt6 import QtWidgets, QtCore


class StatusBar(QtWidgets.QProgressBar):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.timer = QtCore.QTimer(self)
        self.timer_interval = 300
        self.timer.timeout.connect(self.slot_timer)
        self.start()

    def start(self):
        self.timer.start(self.timer_interval)

    def stop(self):
        self.timer.stop()

    def slot_timer(self):
        self.setValue(self.value() + 1)
