#include "tree_model.h"
#include <QTreeView>

class ReordableTreeModel : public TreeModel {

public:
  ReordableTreeModel(const QStringList &headers, QObject *parent = nullptr);
  void appendToDestination(QModelIndex sourceIndex,
                           QModelIndex destinationIndex);
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  Qt::DropActions supportedDropActions() const override;
};

class ReordableTreeView : public QTreeView {
  Q_OBJECT

public:
  ReordableTreeView(QWidget *parent = nullptr);
  ~ReordableTreeView();
  void setModel(ReordableTreeModel *model);
  ReordableTreeModel *model() const;

private:
  void startDrag(Qt::DropActions supportedActions);
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dragLeaveEvent(QDragLeaveEvent *event);

  QModelIndex dragIndex;
  QModelIndex dropIndex;
};
