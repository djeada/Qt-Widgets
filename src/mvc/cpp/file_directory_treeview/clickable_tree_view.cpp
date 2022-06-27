#include "clickable_tree_view.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QDropEvent>
#include <QHeaderView>
#include <QMenu>

ClickableTreeView::ClickableTreeView(QWidget *parent) : QTreeView(parent) {

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &ClickableTreeView::customContextMenuRequested, this,
          &ClickableTreeView::setupContextMenu);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::InternalMove);
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

void ClickableTreeView::startDrag(Qt::DropActions supportedActions) {
  dragIndex = currentIndex();
  QTreeView::startDrag(supportedActions);
}

void ClickableTreeView::dropEvent(QDropEvent *event) {
  dropIndex = indexAt(event->position().toPoint());
  model()->appendToDestination(dragIndex, dropIndex);
}

bool ClickableTreeView::mkdir(const QModelIndex &index, const QString &name) {
  return model()->mkdir(index, name).isValid();
}

bool ClickableTreeView::touch(const QModelIndex &index, const QString &name) {
  return model()->touch(index, name);
}

void ClickableTreeView::removeSelectedIndexes() {
  auto selceted = selectedIndexes();
  for (auto iterator = selceted.end(); iterator-- != selceted.begin();) {
    model()->remove(*iterator);
  }
}

void ClickableTreeView::startCopy(const QModelIndex &sourceIndex) {
  selectedPath = model()->filePath(sourceIndex);
}

void ClickableTreeView::startCut(const QModelIndex &sourceIndex) {
  selectedPath = model()->filePath(sourceIndex);
  previouslySelected = sourceIndex;
}

bool ClickableTreeView::pasteSelected(const QModelIndex &destinationIndex) {
  if (selectedPath.isEmpty()) {
    return true;
  }
  auto flag = model()->paste(destinationIndex, selectedPath);
  if (previouslySelected.isValid()) {
    flag &= model()->remove(previouslySelected);
    previouslySelected = QModelIndex();
    selectedPath = "";
  }
  return flag;
}

void ClickableTreeView::setupContextMenu(const QPoint &pos) {
  auto index = indexAt(pos);
  if (!index.isValid())
    return;
  QMenu menu;
  QList<QString> actionNames = {
      "New Directory", "New File",    "Remove selected", "Rename",
      "Copy",          "Cut",         "Paste",           "Copy Absolute Path",
      "Expand All",    "Collapse All"};
  for (auto &name : actionNames) {
    auto action = new QAction(name, this);
    menu.addAction(action);
  }
  menu.insertSeparator(menu.actions().at(2));
  menu.insertSeparator(menu.actions().at(4));
  menu.insertSeparator(menu.actions().at(10));
  auto selectedAction = menu.exec(mapToGlobal(pos));
  switch (menu.actions().indexOf(selectedAction)) {
  case 0: {
    // create new directory using mkdir
    mkdir(index, "");
    break;
  }
  case 1: {
    // create new file using touch
    touch(index, "");
    break;
  }
  case 3: {
    // remove selected
    removeSelectedIndexes();
    break;
  }
  case 5: {
    // rename selected
    edit(index);
    break;
  }
  case 6: {
    // copy selected
    startCopy(index);
    break;
  }
  case 7: {
    // cut selected
    startCut(index);
    break;
  }
  case 8: {
    // paste selected
    pasteSelected(index);
    break;
  }
  case 9: {
    // copy absolute path
    QApplication::clipboard()->setText(model()->filePath(index));
    break;
  }
  case 11: {
    // expand all
    expandAll();
    break;
  }
  case 12: {
    // collapse all
    collapseAll();
    break;
  }
  }
}

void ClickableTreeView::keyPressEvent(QKeyEvent *event) {
  // check if key is ctrl+c, ctrl+x, ctrl+v or delete
  if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
    removeSelectedIndexes();
  } else if (event->key() == Qt::Key_C &&
             event->modifiers() == Qt::ControlModifier) {
    startCopy(currentIndex());
  } else if (event->key() == Qt::Key_X &&
             event->modifiers() == Qt::ControlModifier) {
    startCut(currentIndex());
  } else if (event->key() == Qt::Key_V &&
             event->modifiers() == Qt::ControlModifier) {
    pasteSelected(currentIndex());
  }

  QTreeView::keyPressEvent(event);
}
