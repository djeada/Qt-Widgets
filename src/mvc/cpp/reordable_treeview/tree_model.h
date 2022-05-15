/*
Based on https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/itemviews/simpletreemodel.
*/

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QVector>

class TreeItem
{
public:
    TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    TreeItem(const QStringList &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void setData(const QVector<QVariant> &data);
    void setParent(TreeItem *parent);

    TreeItem *child(int row);
    int childRow(TreeItem *child);
    QVector<TreeItem*> childrenItems();
    int rowCount() const;
    int columnCount() const;
    int childrenColumnCount() const;
    QVariant data(int column) const;
    QVector<QVariant> data() const;
    int row() const;
    void removeRow(int row);
    void removeRows(int row, int count);
    void removeChild(TreeItem *child);
    void removeChildren();
    TreeItem *parentItem() ;

private:
    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
};

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QVector<QStringList> &data, QObject *parent = nullptr);
    TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex indexFromItem( TreeItem *item) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void appendRow(const QStringList &data);
    void setHorizontalHeaderLabels(const QStringList &labels);
    TreeItem *	item(int row, int column = 0) const;
    TreeItem * item(const QModelIndex &index) const;

private:
    TreeItem *rootItem;
};



#endif // TREEMODEL_H
