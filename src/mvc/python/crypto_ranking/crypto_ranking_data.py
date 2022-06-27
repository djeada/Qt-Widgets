from dataclasses import dataclass


@dataclass
class CryptoRankingData:
    name: str
    iconPath: str
    price: float
    changePercent: float
    volume: float
    marketCap: float
