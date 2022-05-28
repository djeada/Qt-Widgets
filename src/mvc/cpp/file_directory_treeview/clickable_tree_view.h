#include "file_dir_model.h"
#include <QTreeView>

class ClickableTreeView : public QTreeView {
  Q_OBJECT

public:
  ClickableTreeView(QWidget *parent = nullptr);
  ~ClickableTreeView();
  void setModel(FileDirModel *model);
  FileDirModel *model() const;
  bool mkdir(const QModelIndex &index, const QString &name);
  bool touch(const QModelIndex &index, const QString &name);
  bool pasteSelected(const QModelIndex &index);
  void startCopy(const QModelIndex &sourceIndex);
  void startCut(const QModelIndex &sourceIndex);
  void removeSelectedIndexes();

private:
  void startDrag(Qt::DropActions supportedActions);
  void dropEvent(QDropEvent *event);
  QModelIndex dragIndex;
  QModelIndex dropIndex;
  QModelIndex previouslySelected;
  QString selectedPath;
  void setupContextMenu(const QPoint &pos);
  void keyPressEvent(QKeyEvent *event);

};
