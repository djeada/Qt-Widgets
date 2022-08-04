from crypto_ranking_data import CryptoRankingData
from crypto_ranking_table import CryptoRankingModel
from PyQt6 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("main_window.ui", self)
        model = CryptoRankingModel(self)
        data = []
        data.append(
            CryptoRankingData(
                "Bitcoin",
                "images/bitcoin.png",
                8100.0,
                11.56,
                210123282.0,
                361739253420.0,
            )
        )
        data.append(
            CryptoRankingData(
                "Ethereum",
                "images/ethereum.png",
                730.0,
                -10.79,
                76231423.0,
                119951889218.0,
            )
        )
        data.append(
            CryptoRankingData(
                "Ripple", "images/ripple.png", 1.0, 382.23, 3241541123.0, 14866729546.0
            )
        )
        data.append(
            CryptoRankingData(
                "Litecoin",
                "images/litecoin.png",
                100.0,
                -0.23,
                54256561134144.0,
                3169548426.0,
            )
        )
        data.append(
            CryptoRankingData(
                "Bitcoin Cash",
                "images/bitcoin_cash.png",
                800.0,
                -99.9921,
                4532452,
                225250788.0,
            )
        )
        model.setData(data)
        self.tableView.setModel(model)
        self.show()
