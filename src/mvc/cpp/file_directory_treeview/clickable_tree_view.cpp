#include "clickable_tree_view.h"
#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>

ClickableTreeView::ClickableTreeView(QWidget *parent) : QTreeView(parent) {

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &ClickableTreeView::customContextMenuRequested, this,
          [&](const QPoint &pos) {
            QModelIndex index = indexAt(pos);
            if (!index.isValid())
              return;
            QMenu menu;
            QList<QString> actionNames = {"New Directory", "New File", "Remove selected", "Rename selected", "Copy", "Cut", "Paste", "Copy Absolute Path", "Expand All", "Collapse All"};
            for (auto &name : actionNames) {
              auto action = new QAction(name, this);
              menu.addAction(action);
            }
            menu.insertSeparator(menu.actions().at(2));
            menu.insertSeparator(menu.actions().at(5));
            menu.insertSeparator(menu.actions().at(10));
            auto selectedAction = menu.exec(mapToGlobal(pos));
            switch (menu.actions().indexOf(selectedAction)) {
            case 0:{
              // create new directory using mkdir
              model()->mkdir(index, "");
              break;
            }
            case 1:{
              // create new file using touch
              model()->touch(index, "");
              break;
            }
            case 3:{
              // remove selected
              while ( selectedIndexes().size() > 0 ) {
                model()->remove(selectedIndexes().at(0));
              }
              break;
            }
            case 4:{
              // rename selected
              qDebug() << "rename selected";
              edit(index);
              break;
            }
            case 6:{
              // copy selected
              selectedPath = model()->filePath(index);
              break;
            }
            case 7:{
              // cut selected
              selectedPath = model()->filePath(index);
              previouslySelected = index;
              break;
            }
            case 8:{
              // paste selected
              if (selectedPath.isEmpty()) {
                return;
              }
              model()->paste(index, selectedPath);
              if (previouslySelected.isValid()) {
                model()->remove(previouslySelected);
                previouslySelected = QModelIndex();
                selectedPath = "";
              }
              break;
            }
            case 9:{
              // copy absolute path
              QApplication::clipboard()->setText(model()->filePath(index));
              break;
            }
            case 11:{
              // expand all
              expandAll();
              break;
            }
            case 12:{
              // collapse all
              collapseAll();
              break;
            }
            }
          });

  setEditTriggers(QAbstractItemView::NoEditTriggers);
  header()->hide();
  setSelectionMode(QAbstractItemView::ExtendedSelection);
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
