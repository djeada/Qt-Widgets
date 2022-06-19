#include "emoji_picker_tree.h"
#include "emoji_picker_delegate.h"
#include <QHeaderView>

EmojiPickerItem::EmojiPickerItem(const EmojiCategory &category, int columnCount)
    : QStandardItem(), itemCategory(category)
{
   setColumnCount(columnCount);
   setCategory(category);
}


void EmojiPickerItem::setCategory(const EmojiCategory &category)
{
    itemCategory = category;
    setText(category.name);
    for (int i = 0; i * columnCount() < category.emojis.size(); i++) {
        QList<QStandardItem *> items;
        for (auto j = 0; j < columnCount(); ++j) {
            auto next_index = j + i * columnCount();
            if (next_index >= category.emojis.size()) {
                break;
            }
            auto icon = QIcon(category.emojis[next_index].iconPath);
            items.append(new QStandardItem(icon, ""));
        }
        appendRow(items);
    }
}

void EmojiPickerItem::setColumnCount(int count)
{
    QStandardItem::setColumnCount(count);
    setCategory(itemCategory);
}


const EmojiCategory &EmojiPickerItem::category() const
{
    return itemCategory;
}

EmojiPickerModel::EmojiPickerModel(QObject *parent)
    : QStandardItemModel(parent)
{
}


EmojiPickerModel::~EmojiPickerModel()
{
}


void EmojiPickerModel::appendRow(const EmojiCategory &category)
{
    QStandardItemModel::appendRow(new EmojiPickerItem(category, columnCount()));
}


void EmojiPickerModel::appendRow(const QList<EmojiCategory> &categories)
{
    for (int i = 0; i < categories.size(); i++) {
        appendRow(categories[i]);
    }
}


void EmojiPickerModel::clear()
{
    removeRows(0, rowCount());
}

void EmojiPickerModel::setColumnCount(int count)
{
   QStandardItemModel:: setColumnCount(count);
   for (auto item : findItems("", Qt::MatchContains)) {
        item->setColumnCount(count);
 }
}


EmojiPickerTree::EmojiPickerTree(QWidget *parent)
    : QTreeView(parent)
{
    setHeaderHidden(true);
    setItemsExpandable(false);
    setStyleSheet("QTreeView::branch {  border-image: url(none.png); }");
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setItemDelegate(new EmojiPickerDelegate(this));
    header()->setStretchLastSection(false);
}


EmojiPickerTree::~EmojiPickerTree()
{
}


void EmojiPickerTree::setModel(EmojiPickerModel* model)
{
    QTreeView::setModel(model);
    expandAll();
    setIndentation(3);
    header()->setSectionResizeMode(0, QHeaderView::Fixed);
    for (auto column = 0; column < model->columnCount(); column++) {
        header()->setSectionResizeMode(column, QHeaderView::Fixed);
        header()->resizeSection(column, 50);
    }
    for (auto row = 0; row < model->rowCount(); row++) {
        setFirstColumnSpanned(row, QModelIndex(), true);
    }
}


EmojiPickerModel* EmojiPickerTree::model()
{
    return static_cast<EmojiPickerModel*>(QTreeView::model());
}



