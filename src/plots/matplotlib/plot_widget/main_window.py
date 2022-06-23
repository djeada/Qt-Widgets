from PyQt6 import QtWidgets, uic
import numpy as np

from plot_widget import Labels, PlotStyle, Legend, Font


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        x_points = np.linspace(0, 10, 100)
        y_points = np.sin(x_points)
        style = PlotStyle(color_palette=["#E69F00", "#56B4E9", "#009E73", "#F0E442",
                            "#0072B2", "#D55E00", "#CC79A7", "#000000"], background_color="gray", line_style="-", line_width=1,
                          marker_style="o", marker_size=0, grid=True,
                          font=Font(family="Arial", size=12, color="black"))
        self.plot_a.style = style
        self.plot_a.plot(x_points, y_points, Labels("x", "y"), "sin(x) continuous")
        self.plot_a.legend = Legend(["sin(x)"], "upper right")

        style.marker_size = 3
        self.plot_b.style = style
        self.plot_b.scatter(x_points, y_points, Labels("x", "y"), "sin(x) discrete")
        self.plot_b.legend = Legend(["sin(x)"], "upper right")

        self.plot_c.style = style
        self.plot_c.histogram(x_points, Labels("x", "y"), "x points histogram")
        self.plot_c.legend = Legend(["x points"], "upper right")

        self.plot_d.style = style
        self.plot_d.histogram(y_points, Labels("y", "y"), "y points histogram")
        self.plot_d.legend = Legend(["y points"], "upper right")

        self.show()
