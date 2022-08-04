from json_utils import dict_to_json
from player import Player
from PyQt6 import QtCore


def main():
    player = Player("John", 100)
    root = dict()
    player.to_json(root)
    print(root)

    path = "player.json"
    file = QtCore.QFile(path)
    if not file.open(
        QtCore.QIODevice.OpenModeFlag.WriteOnly | QtCore.QIODevice.OpenModeFlag.Text
    ):
        print("Cannot create file")
        return 1
    text_stream = QtCore.QTextStream(file)
    for i, line in enumerate(dict_to_json(root)):
        text_stream << line + "\n"
    file.close()
    print("File created successfully")

    # open file and read json
    if not file.open(QtCore.QIODevice.OpenModeFlag.ReadOnly):
        print("Cannot open file for reading")
        return 1

    data = file.readAll()
    doc = QtCore.QJsonDocument.fromJson(data)
    root2 = doc.object()
    file.close()

    player2 = Player()
    player2.from_json(root2)
    print(player2)
    print(player == player2)

    # remove temp file
    QtCore.QFile.remove(path)


if __name__ == "__main__":
    main()
