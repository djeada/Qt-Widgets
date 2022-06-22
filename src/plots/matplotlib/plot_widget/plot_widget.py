from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure
from matplotlib.ticker import MaxNLocator


class PlotWidget(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        self.fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = self.fig.add_subplot(111)
        self.axes.xaxis.set_major_locator(MaxNLocator(integer=True))
        self.axes.yaxis.set_major_locator(MaxNLocator(integer=True))
        self.axes.grid(True)
        super().__init__(self.fig)
        self.setParent(parent)
        tool_bar = NavigationToolbar(self, parent)

    def plot(self, x, y, xlabel=None, ylabel=None, title=None):
        self.axes.clear()
        self.axes.plot(x, y)
        if xlabel is not None and ylabel is not None:
            self.labels = xlabel, ylabel
        if title is not None:
            self.title = title
        self.draw()

    @property
    def title(self):
        return self.axes.get_title()
    
    @title.setter
    def title(self, title):
        self.axes.set_title(title)

    @property
    def legend(self):
        return self.axes.get_legend()
    
    @legend.setter
    def legend(self, legend):
        self.axes.legend(legend)

    @property
    def labels(self):
        return self.axes.get_xlabel(), self.axes.get_ylabel()
    
    @labels.setter
    def labels(self, labels):
        self.axes.set_xlabel(labels[0])
        self.axes.set_ylabel(labels[1])
    
    @property
    def xlim(self):
        return self.axes.get_xlim()
    
    @xlim.setter
    def xlim(self, xlim):
        self.axes.set_xlim(xlim)

    @property
    def ylim(self):
        return self.axes.get_ylim()
    
    @ylim.setter
    def ylim(self, ylim):
        self.axes.set_ylim(ylim)