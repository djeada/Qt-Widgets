/*
Based on https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/itemviews/simpletreemodel.
*/

#include "tree_model.h"
#include <QStringList>

QVector<QVariant> stringListToVariantList(const QStringList &data)
{
  QVector<QVariant> variantData;
    variantData.reserve(data.count());
    for (auto& string : data)
        variantData.append(QVariant(string));

    return variantData;
}

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : m_itemData(data), m_parentItem(parent)
{


}

TreeItem::TreeItem(const QStringList &data, TreeItem *parent)
    : TreeItem(stringListToVariantList(data), parent)
{

}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{

    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

QVector<TreeItem*> TreeItem::childrenItems()
{
    return m_childItems;
}

int TreeItem::rowCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

int TreeItem::childrenColumnCount() const
{
    int maxCount = 0;
    for (auto& child : m_childItems)
    {
        maxCount = std::max(maxCount, child->columnCount());
    }
    return maxCount;
}

QVariant TreeItem::data(int column) const
{

    if (column < 0 || column >= columnCount())
        return QVariant();

    return m_itemData.at(column);
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
   }

    return 0;
}

void TreeItem::removeRow(int row)
{
    if (row < 0 || row >= rowCount())
        return;
    m_childItems.remove(row);
}


void TreeItem::removeRows(int row, int count)
{
    for (int i = 0; i < count; ++i)
        m_childItems.remove(row);
}


void TreeItem::setData(const QVector<QVariant> &data)
{
    m_itemData = data;
}


TreeModel::TreeModel(const QVector<QStringList> &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem(QStringList() << "Category" << "Description");
    for (auto& row : data)
    {
        appendRow(row);
    }
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem(QStringList() << "Category" << "Description");
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->childrenColumnCount();
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    auto item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    auto childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto childItem = static_cast<TreeItem*>(index.internalPointer());
    auto parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->rowCount();
}

void TreeModel::appendRow(const QStringList &data) {

    auto variantData = stringListToVariantList(data);

 
    rootItem->appendChild(new TreeItem(variantData, rootItem));
}


void TreeModel::setHorizontalHeaderLabels(const QStringList &labels) {
        auto variantData = stringListToVariantList(labels);
    rootItem->setData(variantData);
}


TreeItem * TreeModel::item(const QModelIndex &index) const {
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

TreeItem * TreeModel::item(int row, int column) const {
    return item(index(row, column));
}
