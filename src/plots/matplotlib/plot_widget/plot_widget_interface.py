from abc import ABC, abstractmethod

class PlotWidgetInterface(ABC):
    @abstractmethod
    def plot(self, x, y, title, xlabel, ylabel, legend):
        pass

    @property
    @abstractmethod
    def title(self):
        pass

    @title.setter
    @abstractmethod
    def title(self, title):
        pass

    @property
    @abstractmethod
    def legend(self):
        pass

    @legend.setter
    @abstractmethod
    def legend(self, legend):
        pass

    @property
    @abstractmethod
    def labels(self):
        pass

    @labels.setter
    @abstractmethod
    def labels(self, labels):
        pass

    @property
    @abstractmethod
    def xlim(self):
        pass

    @xlim.setter
    @abstractmethod
    def xlim(self, xlim):
        pass

    @property
    @abstractmethod
    def ylim(self):
        pass

    @ylim.setter
    @abstractmethod
    def ylim(self, ylim):
        pass

    @property
    @abstractmethod
    def style(self):
        pass

    @style.setter
    def style(self, style):
        pass

    @abstractmethod
    def clear(self):
        pass
