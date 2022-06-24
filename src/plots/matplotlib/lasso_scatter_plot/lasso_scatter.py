from plot_widget import PlotWidget
from plot_widget_interface import Labels
from point_selector import SpecialLassoSelector


class LassoScatter(PlotWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._select_from_collection = None

    def scatter(self, x, y, labels: Labels, title: str = ""):
        points = self.axes.scatter(x, y, picker=5)
        self.labels = labels
        self.title = title
        self._select_from_collection = SpecialLassoSelector(self.axes, points)
        self.draw()
