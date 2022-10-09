#include "tree_model.h"
#include <QTreeView>

class ReorderableTreeModel : public TreeModel {

public:
  ReorderableTreeModel(const QStringList &headers, QObject *parent = nullptr);
  void appendToDestination(QModelIndex sourceIndex,
                           QModelIndex destinationIndex);
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  Qt::DropActions supportedDropActions() const override;
};

class ReorderableTreeView : public QTreeView {
  Q_OBJECT

public:
  ReorderableTreeView(QWidget *parent = nullptr);
  ~ReorderableTreeView();
  void setModel(ReorderableTreeModel *model);
  ReorderableTreeModel *model() const;

private:
  void startDrag(Qt::DropActions supportedActions);
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dragLeaveEvent(QDragLeaveEvent *event);

  QModelIndex dragIndex;
  QModelIndex dropIndex;
};
