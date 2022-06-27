from dataclasses import dataclass
from typing import Iterable


@dataclass
class Labels:
    x: str
    y: str


@dataclass
class Legend:
    labels: Iterable[str]
    loc: str


@dataclass
class Font:
    family: str
    size: int
    color: str


@dataclass
class PlotStyle:
    color_palette: Iterable[str]
    background_color: str
    line_style: str
    line_width: int
    marker_style: str
    marker_size: int
    grid: bool
    font: Font


class PlotWidgetInterface:
    def plot(self, x, y, labels: Labels, title: str = ""):
        raise NotImplementedError

    def scatter(self, x, y, labels: Labels, title: str = ""):
        raise NotImplementedError

    def histogram(self, x, labels: Labels, title: str = ""):
        raise NotImplementedError

    def clear(self):
        raise NotImplementedError

    @property
    def style(self):
        raise NotImplementedError

    @style.setter
    def style(self, style: PlotStyle):
        raise NotImplementedError

    @property
    def title(self):
        raise NotImplementedError

    @title.setter
    def title(self, title):
        raise NotImplementedError

    @property
    def legend(self):
        raise NotImplementedError

    @legend.setter
    def legend(self, legend: Legend):
        raise NotImplementedError

    @property
    def labels(self):
        raise NotImplementedError

    @labels.setter
    def labels(self, labels: Labels):
        raise NotImplementedError

    @property
    def xlim(self):
        raise NotImplementedError

    @xlim.setter
    def xlim(self, xlim):
        raise NotImplementedError

    @property
    def ylim(self):
        raise NotImplementedError

    @ylim.setter
    def ylim(self, ylim):
        raise NotImplementedError
