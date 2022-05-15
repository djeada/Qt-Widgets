#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QVector>

class TreeItem {
public:
  TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
  TreeItem(const QStringList &data, TreeItem *parentItem = nullptr);
  ~TreeItem();

  void appendChild(TreeItem *child);
  void setData(const QVector<QVariant> &data);
  void setParent(TreeItem *parent);

  TreeItem *child(int row);
  int childFromRow(TreeItem *child);
  QVector<TreeItem *> childrenItems();
  int rowCount() const;
  int columnCount() const;
  int childrenColumnCount() const;
  QVariant data(int column) const;
  QVector<QVariant> data() const;
  int row() const;
  void removeRow(int row);
  void removeRows(int row, int count);
  void removeChild(TreeItem *child);
  void removeAllChildren();
  TreeItem *parent();
  void removeColumns(int position, int columns);
  void setData(int column, const QVariant &value);
  void insertColumns(int position, int columns);
  void insertRows(int position, int count, int columns);

private:
  QVector<QVariant> itemData;
  TreeItem *parentItem;
  QVector<TreeItem *> childItems;
};

class TreeModel : public QAbstractItemModel {
  Q_OBJECT

public:
  TreeModel(const QStringList &headers, QObject *parent = nullptr);
  ~TreeModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  QModelIndex indexFromItem(TreeItem *item) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  void appendRow(const QStringList &data);
  void setHorizontalHeaderLabels(const QStringList &labels);
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role = Qt::EditRole) override;
  bool insertColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex()) override;
  bool removeColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex()) override;
  TreeItem *item(int row, int column = 0) const;
  TreeItem *itemFromIndex(const QModelIndex &index) const;
  void setReadOnly(bool flag);
  bool isReadOnly() const;

private:
  TreeItem *rootItem;
  bool readOnly;
};

#endif // TREEMODEL_H
