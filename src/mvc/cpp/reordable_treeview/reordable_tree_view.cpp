#include "reordable_tree_view.h"
#include <QDebug>
#include <QMouseEvent>

ReordableTreeModel::ReordableTreeModel(QObject *parent) : TreeModel(parent) {}

void ReordableTreeModel::appendToDestination(QModelIndex sourceIndex,
                                             QModelIndex destinationIndex) {
  auto sourceItem = static_cast<TreeItem *>(sourceIndex.internalPointer());
  auto destinationItem =
      static_cast<TreeItem *>(destinationIndex.internalPointer());
  auto sourceParentItem = sourceItem->parentItem();
  destinationItem->appendChild(sourceItem);
  emit dataChanged(sourceIndex, sourceIndex);
  emit dataChanged(destinationIndex, destinationIndex);
}

Qt::DropActions ReordableTreeModel::supportedDropActions() const {
  return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags ReordableTreeModel::flags(const QModelIndex &index) const {

  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  if (index.isValid())
    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
  else
    return Qt::ItemIsDropEnabled | defaultFlags;
}

ReordableTreeView::ReordableTreeView(QWidget *parent) : QTreeView(parent) {

  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::InternalMove);
}

ReordableTreeView::~ReordableTreeView() {}

ReordableTreeModel *ReordableTreeView::model() const {
  return static_cast<ReordableTreeModel *>(QTreeView::model());
}

void ReordableTreeView::setModel(ReordableTreeModel *model) {
  QTreeView::setModel(model);
}

void ReordableTreeView::startDrag(Qt::DropActions supportedActions) {
  dragIndex = currentIndex();
  QTreeView::startDrag(supportedActions);
}

void ReordableTreeView::dragEnterEvent(QDragEnterEvent *event) {
  QTreeView::dragEnterEvent(event);
}

void ReordableTreeView::dropEvent(QDropEvent *event) {
  dropIndex = indexAt(event->position().toPoint());
  model()->appendToDestination(dragIndex, dropIndex);
  reset();
}

void ReordableTreeView::dragMoveEvent(QDragMoveEvent *event) {
  QTreeView::dragMoveEvent(event);
}

void ReordableTreeView::dragLeaveEvent(QDragLeaveEvent *event) {
  QTreeView::dragLeaveEvent(event);
}
