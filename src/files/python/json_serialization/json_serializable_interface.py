from abc import ABC, abstractmethod

class JsonSerializableInterface(ABC):

    @abstractmethod
    def to_json(self, root) -> None:
        pass

    @abstractmethod
    def from_json(self, root) -> None:
        pass
