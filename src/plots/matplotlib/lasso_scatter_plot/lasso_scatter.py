from enum import Enum, auto

import matplotlib
import numpy as np
from matplotlib.path import Path
from matplotlib.widgets import LassoSelector
from plot_widget import PlotWidget
from plot_widget_interface import Labels
from PyQt6.QtCore import pyqtSignal


class SelectionMode(Enum):
    SELECT = auto()
    DESELECT = auto()


class LassoScatter(PlotWidget):

    selection_changed = pyqtSignal(list)

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._select_from_collection = None
        self._selected_indices = list()
        self._points = list()
        self.selection_mode = SelectionMode.DESELECT

    def scatter(self, x, y, labels: Labels, title: str = ""):
        self._points = self.axes.scatter(x, y, picker=5)
        self.labels = labels
        self.title = title
        self._setup_lasso()
        self.draw()

    def _setup_lasso(self, opacity_factor=0.2):
        self.opacity_factor = opacity_factor
        self._point_offset = self._points.get_offsets()

        # Ensure that we have separate colors for each object
        self._face_colors = self._points.get_facecolors()
        if len(self._face_colors) == 0:
            raise ValueError("No facecolors found on points")
        elif len(self._face_colors) == 1:
            self._face_colors = np.tile(self._face_colors, (len(self._point_offset), 1))
        self._selected_indices = self.all_indices

        old_marker_size = matplotlib.rcParams["lines.markersize"]
        matplotlib.rcParams.update({"lines.markersize": 0})
        self.lasso = LassoSelector(self.axes, onselect=self.on_select)
        matplotlib.rcParams.update({"lines.markersize": old_marker_size})

    @property
    def all_indices(self):
        return tuple(range(len(self._face_colors[:, 0])))

    @property
    def selected_indices(self):
        return self._selected_indices

    @selected_indices.setter
    def selected_indices(self, indices):
        if len(indices) > len(self.all_indices):
            raise ValueError(
                f"Size of indices ({len(indices)}) is larger than size of all indices ({len(self.all_indices)})"
            )
        if len(set(indices)) != len(indices):
            raise ValueError("Indices must be unique")

        self.clear_selection()
        self._selected_indices = indices
        self._face_colors[self.deselected_indices, -1] = self.opacity_factor
        self._points.set_facecolors(self._face_colors)
        self.draw_idle()

    @property
    def deselected_indices(self):
        return tuple(sorted(set(self.all_indices) - set(self.selected_indices)))

    @deselected_indices.setter
    def deselected_indices(self, indices):
        selected_indices = list(set(self.all_indices) - set(indices))
        self.selected_indices = selected_indices

    def clear_selection(self):
        self._selected_indices = self.all_indices
        self.reset_colors()
        self.draw_idle()

    def reset_colors(self):
        self._face_colors[self.all_indices, -1] = 1
        self._points.set_facecolors(self._face_colors)

    def on_select(self, vertices):
        indices_inside_curve = (
            i
            for i, flag in enumerate(Path(vertices).contains_points(self._point_offset))
            if flag
        )
        self.insert_to_current_mode(indices_inside_curve)
        self.selection_changed.emit(self.selected_indices)
        self.draw_idle()

    def insert_to_current_mode(self, indices):
        if self.selection_mode == SelectionMode.SELECT:
            self.selected_indices = list(set(self.selected_indices) | set(indices))
        elif self.selection_mode == SelectionMode.DESELECT:
            self.selected_indices = list(set(self.selected_indices) - set(indices))
