from itertools import chain
import matplotlib
import numpy as np
from matplotlib.collections import PathCollection
from matplotlib.path import Path
from matplotlib.widgets import LassoSelector
from matplotlib.axes._subplots import Axes


class SpecialLassoSelector(LassoSelector):
    def __init__(self, ax: Axes, points: PathCollection, opacity_factor=0.2):
        self._canvas = ax.figure.canvas
        self._points = points
        self.opacity_factor = opacity_factor
        self._point_offset = points.get_offsets()

        # Ensure that we have separate colors for each object
        self._face_colors = points.get_facecolors()
        if len(self._face_colors) == 0:
            raise ValueError("No facecolors found on points")
        elif len(self._face_colors) == 1:
            self._face_colors = np.tile(self._face_colors, (len(self._point_offset), 1))
        self._selected_indices = self.all_indices

        old_marker_size = matplotlib.rcParams['lines.markersize']
        matplotlib.rcParams.update({'lines.markersize': 0})        
        super().__init__(ax, onselect=self.on_select)
        matplotlib.rcParams.update({'lines.markersize': old_marker_size})

    @property
    def all_indices(self):
        return tuple(range(len(self._face_colors[:, 0])))

    @property
    def selected_indices(self):
        return self._selected_indices

    @selected_indices.setter
    def selected_indices(self, indices):
        if (len(indices) > len(self.all_indices)):
            raise ValueError(f"Size of indices ({len(indices)}) is larger than size of all indices ({len(self.all_indices)})")
        if (len(set(indices)) != len(indices)):
            raise ValueError("Indices must be unique")

        self._selected_indices = indices
        self.reset_colors()
        self._canvas.draw_idle()

    @property
    def deselected_indices(self):
        return tuple(sorted(set(self.all_indices) - set(self.selected_indices)))

    @deselected_indices.setter
    def deselected_indices(self, indices):
        selected_indices = list(set(self.all_indices) - set(indices))
        self.selected_indices = selected_indices

    def clear(self):
        self._selected_indices = self.all_indices
        self.reset_colors()
        self._canvas.draw_idle()

    def reset_colors(self):
        self._face_colors[self.all_indices, -1] = 1
        self._points.set_facecolors(self._face_colors)

    def on_select(self, vertices):
        indices_inside_curve = (i for i, flag in enumerate(Path(vertices).contains_points(self._point_offset)) if flag)
        self._selected_indices = list(set(self.all_indices) - set(chain(self.deselected_indices, indices_inside_curve)))
        self._face_colors[self.deselected_indices, -1] = self.opacity_factor
        self._points.set_facecolors(self._face_colors)
        self._canvas.draw_idle()

    def disconnect(self):
        self.disconnect_events()
        self.clear()