#include "crypto_ranking_data.h"
#include <QTableView>

class CryptoRankingModel : public QAbstractTableModel {
  Q_OBJECT

public:
  CryptoRankingModel(QObject *parent = 0);
  CryptoRankingModel(const QList<CryptoRankingData> &data, QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  void setData(const CryptoRankingData &data);
  void setData(const QList<CryptoRankingData> &data);
  void clear();

private:
  QList<CryptoRankingData> modelData;
};

class CryptoRankingTable : public QTableView {
  Q_OBJECT

public:
  CryptoRankingTable(QWidget *parent = 0);
  ~CryptoRankingTable();
  void setModel(CryptoRankingModel *model);
  CryptoRankingModel *getModel();
};
