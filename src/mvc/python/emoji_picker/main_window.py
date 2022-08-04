from emoji_picker_data import EmojiCategory, EmojiData
from emoji_picker_tree import EmojiPickerModel
from PyQt6 import QtWidgets, uic
from PyQt6.QtCore import QDir


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        model = EmojiPickerModel(self)

        iconPaths = []

        # find all paths in images folder
        dir = QDir("images")
        fileInfoList = dir.entryInfoList(QDir.Filter.Files)
        for fileInfo in fileInfoList:
            iconPaths.append(fileInfo.absoluteFilePath())

        emojis = []

        for iconPath in iconPaths:
            emojis.append(EmojiData(iconPath, iconPath, list()))

        category = EmojiCategory("Category A", emojis)
        model.setColumnCount(7)
        model.appendRow(category)
        category.name = "Category B"
        model.appendRow(category)

        self.treeView.setModel(model)

        self.show()
