#include "reordable_tree_view.h"
#include <QMouseEvent>
#include <QDebug>

ReordableTreeModel::ReordableTreeModel(QObject *parent)
    : TreeModel(parent) {
}

void ReordableTreeModel::swapItems(QModelIndex sourceIndex, QModelIndex destinationIndex) {
   
   // Get the source and destination items
    auto sourceItem = static_cast<TreeItem*>(sourceIndex.internalPointer());
    auto destinationItem = static_cast<TreeItem*>(destinationIndex.internalPointer());

    // Append the source children rows from source to destination
    for (auto& child : sourceItem->childrenItems()) {
        destinationItem->appendChild(child);
    }
}


ReordableTreeView::ReordableTreeView(QWidget *parent)
    : QTreeView(parent) {

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
}


ReordableTreeView::~ReordableTreeView() {

}

ReordableTreeModel* ReordableTreeView::model() const {
    return static_cast<ReordableTreeModel*>(QTreeView::model());
}

void ReordableTreeView::setModel(ReordableTreeModel *model) {
    QTreeView::setModel(model);
    connect(model, &ReordableTreeModel::layoutChanged, this, [=]() {
      qDebug() << "layoutChanged";
    });
        connect(model, &ReordableTreeModel::dataChanged, this, [=]() {
          qDebug() << "dataChanged";
        });


}

void ReordableTreeView::startDrag(Qt::DropActions supportedActions) {
    dragIndex = currentIndex();
    QTreeView::startDrag(supportedActions);
}


void ReordableTreeView::dragEnterEvent(QDragEnterEvent *event) {
    QTreeView::dragEnterEvent(event);
}


void ReordableTreeView::dropEvent(QDropEvent *event) {
    qDebug() << "dropEvent";
    dropIndex = indexAt(event->position().toPoint());
    model()->swapItems(dragIndex, dropIndex);
    reset();
    //QTreeView::dropEvent(event);
}


void ReordableTreeView::dragMoveEvent(QDragMoveEvent *event) {
    QTreeView::dragMoveEvent(event);
}


void ReordableTreeView::dragLeaveEvent(QDragLeaveEvent *event) {
    QTreeView::dragLeaveEvent(event);
}



