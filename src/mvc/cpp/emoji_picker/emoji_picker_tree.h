#include "emoji_picker_data.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>

class EmojiPickerItem : public QStandardItem {
public:
  EmojiPickerItem(const EmojiCategory &category, int columnCount);
  void setCategory(const EmojiCategory &category);
  void setColumnCount(int count);
  const EmojiCategory &category() const;
  EmojiCategory itemCategory;
};

class EmojiPickerModel : public QStandardItemModel {
  Q_OBJECT

public:
  EmojiPickerModel(QObject *parent = nullptr);
  ~EmojiPickerModel();
  void appendRow(const EmojiCategory &category);
  void appendRow(const QList<EmojiCategory> &categories);
  void clear();
  void setColumnCount(int count);
};

class EmojiPickerTree : public QTreeView {
  Q_OBJECT

public:
  EmojiPickerTree(QWidget *parent = nullptr);
  ~EmojiPickerTree();
  void setModel(EmojiPickerModel *model);
  EmojiPickerModel *model();
};
