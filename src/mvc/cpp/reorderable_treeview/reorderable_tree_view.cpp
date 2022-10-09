#include "reorderable_tree_view.h"
#include <QDebug>
#include <QMouseEvent>

ReorderableTreeModel::ReorderableTreeModel(const QStringList &headers,
                                       QObject *parent)
    : TreeModel(headers, parent) {}

void ReorderableTreeModel::appendToDestination(QModelIndex sourceIndex,
                                             QModelIndex destinationIndex) {
  auto sourceItem = static_cast<TreeItem *>(sourceIndex.internalPointer());
  auto destinationItem =
      static_cast<TreeItem *>(destinationIndex.internalPointer());
  destinationItem->appendChild(sourceItem);
  emit dataChanged(sourceIndex, sourceIndex);
  emit dataChanged(destinationIndex, destinationIndex);
}

Qt::DropActions ReorderableTreeModel::supportedDropActions() const {
  return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags ReorderableTreeModel::flags(const QModelIndex &index) const {

  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  if (index.isValid())
    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
  else
    return Qt::ItemIsDropEnabled | defaultFlags;
}

ReorderableTreeView::ReorderableTreeView(QWidget *parent) : QTreeView(parent) {

  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::InternalMove);
}

ReorderableTreeView::~ReorderableTreeView() {}

ReorderableTreeModel *ReorderableTreeView::model() const {
  return static_cast<ReorderableTreeModel *>(QTreeView::model());
}

void ReorderableTreeView::setModel(ReorderableTreeModel *model) {
  QTreeView::setModel(model);
}

void ReorderableTreeView::startDrag(Qt::DropActions supportedActions) {
  dragIndex = currentIndex();
  QTreeView::startDrag(supportedActions);
}

void ReorderableTreeView::dragEnterEvent(QDragEnterEvent *event) {
  QTreeView::dragEnterEvent(event);
}

void ReorderableTreeView::dropEvent(QDropEvent *event) {
  dropIndex = indexAt(event->position().toPoint());
  model()->appendToDestination(dragIndex, dropIndex);
  reset();
  expandAll();
}

void ReorderableTreeView::dragMoveEvent(QDragMoveEvent *event) {
  QTreeView::dragMoveEvent(event);
}

void ReorderableTreeView::dragLeaveEvent(QDragLeaveEvent *event) {
  QTreeView::dragLeaveEvent(event);
}
