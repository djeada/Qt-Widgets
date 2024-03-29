import numpy as np
from plot_widget import Font, PlotStyle
from PyQt6 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        x_points = np.linspace(0, 10, 100)
        y_points = np.sin(x_points)
        style = PlotStyle(
            color_palette=[
                "#E69F00",
                "#56B4E9",
                "#009E73",
                "#F0E442",
                "#0072B2",
                "#D55E00",
                "#CC79A7",
                "#000000",
            ],
            background_color="gray",
            line_style="-",
            line_width=1,
            marker_style="o",
            marker_size=0,
            grid=True,
            font=Font(family="Arial", size=12, color="black"),
        )
        self.histogramFilter.style = style
        self.histogramFilter.array = y_points
        self.show()
