#include <QTreeView>
#include "file_dir_model.h"

class ClickableTreeView : public QTreeView {
  Q_OBJECT

public:
  ClickableTreeView(QWidget *parent = nullptr);
  ~ClickableTreeView();
  void addChild(QModelIndex index);
  void removeItem(QModelIndex index);
  void editItem(QModelIndex index);
  void setModel(FileDirModel *model);
  FileDirModel *model() const;
private:
  QModelIndex previouslySelected;
  QString selectedPath;
};
