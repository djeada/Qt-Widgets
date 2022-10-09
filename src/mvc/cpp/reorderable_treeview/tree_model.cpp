#include "tree_model.h"
#include <QStringList>
#include <exception>

QVector<QVariant> stringListToVariantList(const QStringList &data) {
  QVector<QVariant> variantData;
  variantData.reserve(data.count());
  for (auto &string : data) {
    variantData.append(QVariant(string));
  }
  return variantData;
}

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : itemData(data), parentItem(parent) {}

TreeItem::TreeItem(const QStringList &data, TreeItem *parent)
    : TreeItem(stringListToVariantList(data), parent) {}

TreeItem::~TreeItem() { qDeleteAll(childItems); }

void TreeItem::appendChild(TreeItem *item) {
  if (!item) {
    return;
  }

  auto currentParent = item->parent();
  if (currentParent) {
    currentParent->removeChild(item);
  }
  item->setParent(this);
  childItems.append(item);
}

TreeItem *TreeItem::child(int row) {
  if (row < 0 || row >= childItems.size()) {
    return nullptr;
  }
  return childItems.at(row);
}

int TreeItem::childFromRow(TreeItem *child) {
  return childItems.indexOf(child);
}

QVector<TreeItem *> TreeItem::childrenItems() { return childItems; }

int TreeItem::rowCount() const { return childItems.count(); }

int TreeItem::columnCount() const { return itemData.count(); }

int TreeItem::childrenColumnCount() const {
  int maxCount = 0;
  for (auto &child : childItems) {
    maxCount = std::max(maxCount, child->columnCount());
  }
  return maxCount;
}

QVariant TreeItem::data(int column) const {

  if (column < 0 || column >= columnCount()) {
    return QVariant();
  }
  return itemData.at(column);
}

QVector<QVariant> TreeItem::data() const { return itemData; }

TreeItem *TreeItem::parent() { return parentItem; }

int TreeItem::row() const {
  if (parentItem) {
    return parentItem->childItems.indexOf(const_cast<TreeItem *>(this));
  }

  return 0;
}

void TreeItem::removeRow(int row) {
  if (row < 0 || row >= rowCount()) {
    return;
  }
  childItems.remove(row);
}

void TreeItem::removeRows(int row, int count) {
  for (int i = 0; i < count; ++i) {
    childItems.remove(row);
  }
}

void TreeItem::removeChild(TreeItem *child) { childItems.removeOne(child); }

void TreeItem::removeAllChildren() { childItems.clear(); }

void TreeItem::setData(const QVector<QVariant> &data) { itemData = data; }

void TreeItem::setParent(TreeItem *parent) {
  if (!parent) {
    return;
  }

  parentItem = parent;
}

void TreeItem::removeColumns(int position, int columns) {
  if (position < 0 || position + columns > itemData.size()) {
    throw std::out_of_range("removeColumns: invalid arguments");
  }

  for (int column = 0; column < columns; column++) {
    itemData.remove(position);
  }

  for (const auto &child : childItems) {
    child->removeColumns(position, columns);
  }
}

void TreeItem::insertColumns(int position, int columns) {
  if (position < 0 || position > itemData.size()) {
    throw std::out_of_range("insertColumns: invalid arguments");
  }

  for (int column = 0; column < columns; ++column) {
    itemData.insert(position, QVariant());
  }

  for (const auto &child : childItems) {
    child->insertColumns(position, columns);
  }
}

void TreeItem::insertRows(int position, int count, int columns) {
  if (position < 0 || position > childItems.size()) {
    throw std::out_of_range("insertRows: invalid arguments");
  }

  for (int row = 0; row < count; ++row) {
    QVector<QVariant> data(columns);
    auto item = new TreeItem(data, this);
    childItems.insert(position, item);
  }
}

void TreeItem::setData(int column, const QVariant &value) {
  if (column < 0 || column >= itemData.size()) {
    throw std::out_of_range("setData: invalid arguments");
  }

  itemData[column] = value;
}

TreeModel::TreeModel(const QStringList &headers, QObject *parent)
    : QAbstractItemModel(parent), readOnly(false) {
  QVector<QVariant> rootData;
  for (const QString &header : headers) {
    rootData << header;
  }

  rootItem = new TreeItem(rootData);
}

TreeModel::~TreeModel() { delete rootItem; }

void TreeModel::setReadOnly(bool flag) { readOnly = flag; }

bool TreeModel::isReadOnly() const { return readOnly; }

int TreeModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return static_cast<TreeItem *>(parent.internalPointer())
        ->childrenColumnCount();
  }
  return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    auto item = static_cast<TreeItem *>(index.internalPointer());
    return item->data(index.column());
  }

  return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {

  if (!index.isValid()) {
    return Qt::NoItemFlags;
  }

  if (readOnly) {
    return QAbstractItemModel::flags(index);
  }

  if (hasChildren(index)) {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  } else {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  return Qt::ItemIsEnabled;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return rootItem->data(section);
  }

  return QVariant();
}

QModelIndex TreeModel::index(int row, int column,
                             const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  TreeItem *parentItem;

  if (!parent.isValid()) {
    parentItem = rootItem;
  } else {
    parentItem = static_cast<TreeItem *>(parent.internalPointer());
  }

  auto childItem = parentItem->child(row);

  if (childItem) {
    return createIndex(row, column, childItem);
  }

  return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) {
    return QModelIndex();
  }

  auto childItem = static_cast<TreeItem *>(index.internalPointer());
  auto parentItem = childItem->parent();

  if (parentItem == rootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
  TreeItem *parentItem;
  if (parent.column() > 0) {
    return 0;
  }

  if (!parent.isValid()) {
    parentItem = rootItem;
  } else {
    parentItem = static_cast<TreeItem *>(parent.internalPointer());
  }

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

TreeItem *TreeModel::itemFromIndex(const QModelIndex &index) const {
  if (index.isValid()) {
    auto item = static_cast<TreeItem *>(index.internalPointer());
    if (item) {
      return item;
    }
  }
  return rootItem;
}

TreeItem *TreeModel::item(int row, int column) const {
  return itemFromIndex(index(row, column));
}

QModelIndex TreeModel::indexFromItem(TreeItem *item) const {
  if (item == rootItem) {
    return QModelIndex();
  }

  return createIndex(item->row(), 0, item);
}

bool TreeModel::removeColumns(int position, int columns,
                              const QModelIndex &parent) {
  beginRemoveColumns(parent, position, position + columns - 1);
  try {
    rootItem->removeColumns(position, columns);
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    endRemoveColumns();
    return false;
  }
  endRemoveColumns();

  if (rootItem->columnCount() == 0) {
    removeRows(0, rowCount());
  }

  return true;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent) {
  auto parentItem = itemFromIndex(parent);
  if (!parentItem) {
    return false;
  }

  beginRemoveRows(parent, position, position + rows - 1);
  try {
    parentItem->removeRows(position, rows);
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    endRemoveRows();
    return false;
  }
  endRemoveRows();

  return true;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                        int role) {
  if (role != Qt::EditRole) {
    return false;
  }

  auto item = itemFromIndex(index);
  try {
    item->setData(index.column(), value);
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    return false;
  }
  emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
  return true;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {
  if (role != Qt::EditRole || orientation != Qt::Horizontal) {
    return false;
  }

  try {
    rootItem->setData(section, value);
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    return false;
  }

  emit headerDataChanged(orientation, section, section);
  return true;
}

bool TreeModel::insertColumns(int position, int columns,
                              const QModelIndex &parent) {
  beginInsertColumns(parent, position, position + columns - 1);
  try {
    rootItem->insertColumns(position, columns);
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    endInsertColumns();
    return false;
  }
  endInsertColumns();
  return true;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent) {
  auto parentItem = itemFromIndex(parent);
  if (!parentItem) {
    return false;
  }

  beginInsertRows(parent, position, position + rows - 1);
  try {
    parentItem->insertRows(position, rows, rootItem->columnCount());
  } catch (std::out_of_range &e) {
    qDebug() << e.what();
    endInsertRows();
    return false;
  }
  endInsertRows();

  return true;
}
