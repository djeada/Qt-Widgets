#include "crypto_ranking_table.h"
#include "crypto_ranking_delegate.h"

CryptoRankingModel::CryptoRankingModel(QObject *parent) : QAbstractTableModel(parent) {
}

CryptoRankingModel::CryptoRankingModel(const QList<CryptoRankingData> &data, QObject *parent) : QAbstractTableModel(parent)
{
    modelData = data;
}

int CryptoRankingModel::rowCount(const QModelIndex &parent) const
{
    return modelData.size();
}


int CryptoRankingModel::columnCount(const QModelIndex &parent) const
{
    // number of fields in CryptoRankingData
    return 5;
}


QVariant CryptoRankingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return modelData[index.row()].name;
        case 1:
            return modelData[index.row()].price;
        case 2:
            return modelData[index.row()].changePercent;
        case 3:
            return modelData[index.row()].volume;
        case 4:
            return modelData[index.row()].marketCap;
        default:
            return QVariant();
        }

    }
    else if (role == Qt::DecorationRole)
    {
        if (index.column() == 0)
        {
            return QIcon(modelData[index.row()].iconPath);
        }
        else if (index.column() == 2)
        {
            auto value = modelData[index.row()].changePercent;
            if (value > 0)
                return QIcon("images/up.png");
            else if (value < 0)
                return QIcon("images/down.png");
        }   
    }

    return QVariant();
}


QVariant CryptoRankingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Name");
            case 1:
                return QString("Price");
            case 2:
                return QString("Change");
            case 3:
                return QString("Volume");
            case 4:
                return QString("Market Cap");
            default:
                return QVariant();
            }
        }
        else if (orientation == Qt::Vertical)
        {
            return section + 1;
        }
    }
    return QVariant();
}


void CryptoRankingModel::setData(const CryptoRankingData &data)
{
    modelData.append(data);
}


void CryptoRankingModel::setData(const QList<CryptoRankingData> &data)
{
    modelData = data;
}


void CryptoRankingModel::clear()
{
    modelData.clear();
}


CryptoRankingTable::CryptoRankingTable(QWidget *parent) : QTableView(parent) {
    //set the delegate for the table
    setItemDelegate(new CryptoRankingDelegate(this));
}

CryptoRankingTable::~CryptoRankingTable() {}

void CryptoRankingTable::setModel(CryptoRankingModel *model)
{
    QTableView::setModel(model);
}

CryptoRankingModel * CryptoRankingTable::getModel()
{
    return static_cast<CryptoRankingModel *>(QTableView::model());
}

