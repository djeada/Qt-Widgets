from PyQt6.QtCore import Qt, QModelIndex, QPoint
from PyQt6.QtWidgets import QAbstractItemView, QMenu, QTreeView


class ReorderableTreeView(QTreeView):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

        self.setDragEnabled(True)
        self.setAcceptDrops(True)
        self.setDropIndicatorShown(True)
        self.setDragDropMode(QAbstractItemView.DragDropMode.InternalMove)
        self.setSelectionMode(QAbstractItemView.SelectionMode.SingleSelection)

        self._cut_index = QModelIndex()
        self._drag_index = QModelIndex()

    def move_to_destination(self, source_index, destination_index):
        self.model().move_to_destination(source_index, destination_index)
        self.expandAll()
        self.clearSelection()

    def startDrag(self, event):
        self._drag_index = self.currentIndex()
        super().startDrag(event)

    def dropEvent(self, event):
        position = QPoint(int(event.position().x()), int(event.position().y()))
        index = self.indexAt(position)
        self.move_to_destination(self._drag_index, index)

    def contextMenuEvent(self, event):
        global_position = event.globalPos()
        position = self.viewport().mapFromGlobal(global_position)
        index = self.indexAt(position)

        menu = QMenu(self)
        cut_action = menu.addAction("Cut")
        copy_action = menu.addAction("Copy")
        paste_action = menu.addAction("Paste")
        delete_action = menu.addAction("Delete")

        action = menu.exec(global_position)
        if action == cut_action:
            self._cut_index = index
        elif action == copy_action:
            pass
        elif action == paste_action:
            self.move_to_destination(self._cut_index, index)
        elif action == delete_action:
            self.model().removeRow(index.row(), index.parent())
