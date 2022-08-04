import matplotlib
from cycler import cycler
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure
from matplotlib.ticker import MaxNLocator
from plot_widget_interface import Font, Labels, Legend, PlotStyle, PlotWidgetInterface


class PlotWidget(FigureCanvas, PlotWidgetInterface):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        self.fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = self.fig.add_subplot(111)
        self.axes.xaxis.set_major_locator(MaxNLocator(integer=True))
        self.axes.yaxis.set_major_locator(MaxNLocator(integer=True))
        self.axes.grid(True)
        super().__init__(self.fig)
        self.setParent(parent)
        NavigationToolbar(self, parent)

    def plot(self, x, y, labels: Labels, title: str = ""):
        self.axes.clear()
        self.axes.plot(x, y)
        self.labels = labels
        self.title = title
        self.draw()

    def scatter(self, x, y, labels: Labels, title: str = ""):
        self.axes.clear()
        self.axes.scatter(x, y)
        self.labels = labels
        self.title = title
        self.draw()

    def histogram(self, x, labels: Labels, title: str = ""):
        self.axes.clear()
        self.axes.hist(x)
        self.labels = labels
        self.title = title
        self.draw()

    def clear(self):
        self.axes.clear()
        self.draw()

    @property
    def style(self):
        color_palette = matplotlib.rcParams["axes.prop_cycle"].by_key()["color"]
        background_color = matplotlib.rcParams["axes.edgecolor"]
        line_style = matplotlib.rcParams["lines.linestyle"]
        line_width = matplotlib.rcParams["lines.linewidth"]
        marker_style = matplotlib.rcParams["lines.marker"]
        marker_size = matplotlib.rcParams["lines.markersize"]
        grid = matplotlib.rcParams["axes.grid"]
        font = Font(
            family=matplotlib.rcParams["font.family"],
            size=matplotlib.rcParams["font.size"],
            color=matplotlib.rcParams["text.color"],
        )
        return PlotStyle(
            color_palette=color_palette,
            background_color=background_color,
            line_style=line_style,
            line_width=line_width,
            marker_style=marker_style,
            marker_size=marker_size,
            grid=grid,
            font=font,
        )

    @style.setter
    def style(self, style: PlotStyle):
        default_size = style.font.size
        small_size = 0.8 * default_size
        big_size = 1.2 * default_size
        matplotlib.rcParams.update({"font.family": style.font.family})
        matplotlib.rcParams.update({"font.size": default_size})
        matplotlib.rcParams.update({"text.color": style.font.color})
        matplotlib.rcParams.update(
            {"axes.prop_cycle": cycler("color", style.color_palette)}
        )
        matplotlib.rcParams.update({"axes.edgecolor": "none"})
        matplotlib.rcParams.update({"axes.axisbelow": True})
        matplotlib.rcParams.update({"axes.grid": True})
        matplotlib.rcParams.update(
            {"axes.facecolor": style.background_color}
        )  # legend background color
        matplotlib.rcParams.update(
            {"figure.facecolor": style.background_color}
        )  # figure background color
        matplotlib.rcParams.update(
            {"savefig.facecolor": style.background_color}
        )  # figure background color
        matplotlib.rcParams.update({"axes.linewidth": style.line_width})
        matplotlib.rcParams.update({"axes.grid": style.grid})
        matplotlib.rcParams.update({"axes.labelcolor": style.font.color})
        matplotlib.rcParams.update({"axes.labelsize": big_size})
        matplotlib.rcParams.update({"axes.titlesize": big_size})
        matplotlib.rcParams.update({"axes.titlecolor": style.font.color})
        matplotlib.rcParams.update({"lines.color": style.font.color})
        matplotlib.rcParams.update({"xtick.direction": "out"})
        matplotlib.rcParams.update({"ytick.direction": "out"})
        matplotlib.rcParams.update({"xtick.color": style.font.color})
        matplotlib.rcParams.update({"ytick.color": style.font.color})
        matplotlib.rcParams.update({"xtick.labelsize": small_size})
        matplotlib.rcParams.update({"ytick.labelsize": small_size})
        matplotlib.rcParams.update({"lines.marker": style.marker_style})
        matplotlib.rcParams.update({"lines.markersize": style.marker_size})
        # figure background color
        self.axes.set_facecolor(style.background_color)
        self.draw()

    @property
    def title(self):
        return self.axes.get_title()

    @title.setter
    def title(self, title):
        self.axes.set_title(title)

    @property
    def legend(self) -> Legend:
        return Legend(
            self.axes.get_legend_handles_labels()[1], self.axes.get_legend_loc()
        )

    @legend.setter
    def legend(self, legend: Legend):
        self.axes.legend(legend.labels, loc=legend.loc)
        self.draw()

    @property
    def labels(self) -> Labels:
        return Labels(self.axes.get_xlabel(), self.axes.get_ylabel())

    @labels.setter
    def labels(self, labels: Labels):
        self.axes.set_xlabel(labels.x, fontsize=1.2 * self.style.font.size)
        self.axes.set_ylabel(labels.y, fontsize=1.2 * self.style.font.size)

    @property
    def xlim(self):
        return self.axes.get_xlim()

    @xlim.setter
    def xlim(self, value):
        self.axes.set_xlim(value)

    @property
    def ylim(self):
        return self.axes.get_ylim()

    @ylim.setter
    def ylim(self, value):
        self.axes.set_ylim(value)
