from json_serializable_interface import JsonSerializableInterface

class Player(JsonSerializableInterface):
    def __init__(self, name="", score=0):
        self.name = name
        self.score = score

    def to_json(self, root):
        root["name"] = self.name
        root["score"] = self.score

    def from_json(self, root):
        self.name = root["name"].toString()
        self.score = root["score"].toInt()

    def __eq__(self, other):
        return self.name == other.name and self.score == other.score

    def __str__(self):
        return "Player(" + self.name + ", " + str(self.score) + ")"

    def __repr__(self):
        return self.__str__()

    def __hash__(self):
        return hash(self.name) + hash(self.score)

    def __lt__(self, other):
        return self.score < other.score

    def __gt__(self, other):
        return self.score > other.score

    def __le__(self, other):
        return self.score <= other.score

    def __ge__(self, other):
        return self.score >= other.score

    def __ne__(self, other):
        return not (self == other)