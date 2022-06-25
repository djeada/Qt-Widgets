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
                          marker_style="o", marker_size=5, grid=True,
                          font=Font(family="Arial", size=12, color="black"))
        self.plot.style = style
        self.plot.scatter(x_points, y_points, Labels(x="x", y="y"), title="Lasso Scatter Plot")
        self.plot.legend = Legend(loc="upper right", labels=["sin(x)"])

        # 1 column is x_points, 2 column is y_points
        matrix = np.array([x_points, y_points])
        self.tableWidget.matrix = matrix.T
        self.tableWidget.horizontal_header = ["x", "y"]
        self.tableWidget.checkable = True
        self.tableWidget.resizeColumnsToContents()

        self.show()
