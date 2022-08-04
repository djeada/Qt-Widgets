import numpy as np
from plot_widget_interface import Labels
from PyQt6 import uic
from PyQt6.QtCore import QCoreApplication, QRect
from PyQt6.QtGui import QResizeEvent
from PyQt6.QtWidgets import QWidget


class FilterHistogram(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi("filter_histogram.ui", self)
        self._array = np.array([])
        # post resize event
        QCoreApplication.postEvent(self, QResizeEvent(self.size(), self.size()))
        self.slider.value_changed.connect(lambda _: self.update_histogram())
        self._n_bins = 30

    def update_histogram(self):
        self.plot.histogram(
            self.array,
            self.n_bins,
            disabled_bins=self.disabled_bins,
            labels=Labels(x="data", y="count"),
        )
        print(self.filtered_array(), len(self.filtered_array()))

    @property
    def n_bins(self):
        return self._n_bins

    @n_bins.setter
    def n_bins(self, value):
        self._n_bins = value
        self.update_histogram()

    @property
    def disabled_bins(self):
        # bins below min_value and above max_value are disabled
        min_value = self.slider.min_value if self.slider.min_value != 0 else -1
        max_value = self.slider.max_value
        bins_range = np.array(range(self.n_bins))
        disabled_bins = bins_range[
            (bins_range <= min_value * self.n_bins // 100)
            | (bins_range >= max_value * self.n_bins // 100)
        ]
        return list(disabled_bins)

    @disabled_bins.setter
    def disabled_bins(self, value):
        self.slider.min_value = min(value)
        self.slider.max_value = max(value)
        self.update_histogram()

    @property
    def style(self):
        return self.plot.style

    @style.setter
    def style(self, value):
        self.plot.style = value

    @property
    def array(self):
        return self._array

    @array.setter
    def array(self, value):
        self._array = value
        self.update_histogram()

    def filtered_array_indices(self):
        bins = np.linspace(np.min(self.array), np.max(self.array), self.n_bins + 1)
        indices = list()

        for i, edge in enumerate(bins[1:]):
            if i in self.disabled_bins:
                continue
            previous_edge = bins[i - 1]
            indices_from_range = np.where(
                (self.array >= previous_edge) & (self.array <= edge)
            )[0]
            indices.extend(indices_from_range)

        return sorted(set(indices))

    def filtered_array(self):
        return self.array[self.filtered_array_indices()]

    def resizeEvent(self, event):
        self.slider.setGeometry(
            QRect(
                self.slider.x() + 0.15 * self.width(),
                self.slider.y(),
                0.7 * self.width(),
                self.slider.height(),
            )
        )
        super().resizeEvent(event)
