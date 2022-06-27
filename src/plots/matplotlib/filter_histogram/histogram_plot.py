from typing import List

import numpy as np

from plot_widget import PlotWidget
from plot_widget_interface import Labels


class HistogramPlot(PlotWidget):


    def histogram(self, array: np.ndarray, n_bins:int, labels: Labels = None, disabled_bins: List[int] = list(), enabled_bins_color="#E69F00", disabled_bins_color="#000000"):
        self.clear()
        n, bins, patches = self.axes.hist(array, color=enabled_bins_color, alpha=0.5, bins=n_bins)


        for i, patch in enumerate(patches):
            if i in disabled_bins:
                patch.set_facecolor(disabled_bins_color)

        if labels is not None:
            self.labels = labels

        self.draw()