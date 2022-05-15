#include "clickable_tree_view.h"
#include <QAction>
#include <QMenu>

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
}

ClickableTreeView::~ClickableTreeView() {}

TreeModel *ClickableTreeView::model() const {
  return static_cast<TreeModel *>(QTreeView::model());
}

void ClickableTreeView::setModel(TreeModel *model) {
  QTreeView::setModel(model);
}

void ClickableTreeView::addChild(QModelIndex index) {
  auto model = this->model();
  model->itemFromIndex(index)->appendChild(
      new TreeItem(QStringList() << "New Item", model->itemFromIndex(index)));
  expandAll();
}

void ClickableTreeView::removeItem(QModelIndex index) {
  auto model = this->model();
  model->itemFromIndex(index)->parent()->removeChild(
      model->itemFromIndex(index));
  expandAll();
}

void ClickableTreeView::editItem(QModelIndex index) { edit(index); }
