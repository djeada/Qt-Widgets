#include "clickable_tree_view.h"
#include <QAction>
#include <QMenu>
#include <QHeaderView>

ClickableTreeView::ClickableTreeView(QWidget *parent) : QTreeView(parent) {

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &ClickableTreeView::customContextMenuRequested, this,
          [&](const QPoint &pos) {
            QModelIndex index = indexAt(pos);
            if (!index.isValid())
              return;
            QMenu menu;
            auto addChildAction = menu.addAction("Add Child");
            auto removeItemAction = menu.addAction("Remove Item");
            auto editItemAction = menu.addAction("Edit Item");
            auto selectedAction = menu.exec(mapToGlobal(pos));
            switch (menu.actions().indexOf(selectedAction)) {
            case 0:
              addChild(index);
              break;
            case 1:
              removeItem(index);
              break;
            case 2:
              editItem(index);
              break;
            default:
              break;
            }
          });

  setEditTriggers(QAbstractItemView::NoEditTriggers);
  // hide header
  header()->hide();
}

ClickableTreeView::~ClickableTreeView() {}

FileDirModel *ClickableTreeView::model() const {
  return static_cast<FileDirModel *>(QTreeView::model());
}

void ClickableTreeView::setModel(FileDirModel *model) {
  QTreeView::setModel(model);
  // hide all columns except the first one
  for (int i = 1; i < model->columnCount(); ++i)
    hideColumn(i);
}

void ClickableTreeView::addChild(QModelIndex index) {
  auto model = this->model();

  expandAll();
}

void ClickableTreeView::removeItem(QModelIndex index) {
  auto model = this->model();

  expandAll();
}

void ClickableTreeView::editItem(QModelIndex index) { edit(index); }
