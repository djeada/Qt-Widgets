#include "main_window.h"
#include "./ui_main_window.h"
#include <QModelIndex>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new CryptoRankingModel(this);
  QList<CryptoRankingData> data;
  data.append(CryptoRankingData{"Bitcoin", "images/bitcoin.png", 8100.0, 11.56,
                                210123282., 361739253420.});
  data.append(CryptoRankingData{"Ethereum", "images/ethereum.png", 730.0,
                                -10.79, 76231423., 119951889218.});
  data.append(CryptoRankingData{"Ripple", "images/ripple.png", 1.0, 382.23,
                                3241541123., 14866729546.});
  data.append(CryptoRankingData{"Litecoin", "images/litecoin.png", 100.0, -0.23,
                                54256561134144., 3169548426.});
  data.append(CryptoRankingData{"Bitcoin Cash", "images/bitcoin_cash.png",
                                800.0, -99.9921, 4532452, 225250788.});
  model->setData(data);
  ui->tableView->setModel(model);
}

MainWindow::~MainWindow() { delete ui; }
