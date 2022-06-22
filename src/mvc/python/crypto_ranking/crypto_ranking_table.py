from PyQt6.QtCore import QAbstractTableModel, QVariant, Qt
from PyQt6.QtGui import QIcon
from PyQt6.QtWidgets import QTableView

from crypto_ranking_delegate import CryptoRankingDelegate


class CryptoRankingModel(QAbstractTableModel):
    def __init__(self, parent=None):
        super(CryptoRankingModel, self).__init__(parent)
        self.modelData = []

    def rowCount(self, parent):
        return len(self.modelData)
    
    def columnCount(self, parent):
        return 5

    def data(self, index, role):
        if not index.isValid():
            return QVariant()
        
        if role ==  Qt.ItemDataRole.DisplayRole:
            if index.column() == 0:
                return self.modelData[index.row()].name
            elif index.column() == 1:
                return self.modelData[index.row()].price
            elif index.column() == 2:
                return self.modelData[index.row()].changePercent
            elif index.column() == 3:
                return self.modelData[index.row()].volume
            elif index.column() == 4:
                return self.modelData[index.row()].marketCap
            else:
                return QVariant()
        elif role == Qt.ItemDataRole.DecorationRole:
            if index.column() == 0:
                return QIcon(self.modelData[index.row()].iconPath)
            elif index.column() == 2:
                value = self.modelData[index.row()].changePercent
                if value > 0:
                    return QIcon("images/up.png")
                elif value < 0:
                    return QIcon("images/down.png")
        return QVariant()

    def headerData(self, section, orientation, role):
        if role == Qt.ItemDataRole.DisplayRole:
            if orientation == Qt.Orientation.Horizontal:
                if section == 0:
                    return "Name"
                elif section == 1:
                    return "Price"
                elif section == 2:
                    return "Change"
                elif section == 3:
                    return "Volume"
                elif section == 4:
                    return "Market Cap"
                else:
                    return QVariant()
            elif orientation == Qt.Orientation.Vertical:
                return section + 1
        return QVariant()

    def setData(self, data):
        self.modelData.append(data)

    def setData(self, data):
        self.modelData = data

    def clear(self):
        self.modelData.clear()

    
class CryptoRankingTable(QTableView):
    def __init__(self, parent=None):
        super(CryptoRankingTable, self).__init__(parent)
        self.setItemDelegate(CryptoRankingDelegate(self))

    def setModel(self, model):
        super().setModel(model)

    def getModel(self):
        return super().getModel()

    