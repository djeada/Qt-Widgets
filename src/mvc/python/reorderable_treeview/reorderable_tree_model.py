from PyQt6.QtCore import Qt

from tree_model import TreeModel


class ReorderableTreeModel(TreeModel):
    def __init__(self, parent=None):
        super().__init__(parent, read_only=True)

    def move_to_destination(self, source_index, destination_index):
        source_item = self.itemFromIndex(source_index)
        destination_item = self.itemFromIndex(destination_index)
        destination_item.append_child(source_item)
        self.dataChanged.emit(source_index, source_index)
        self.dataChanged.emit(destination_index, destination_index)

    def flags(self, index):
        return (
            super().flags(index)
            | Qt.ItemFlag.ItemIsDragEnabled
            | Qt.ItemFlag.ItemIsDropEnabled
        )

    def supportedDropActions(self):
        return Qt.DropAction.CopyAction | Qt.DropAction.MoveAction
