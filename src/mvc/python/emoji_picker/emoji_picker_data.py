from dataclasses import dataclass


@dataclass
class EmojiData:
    name: str
    iconPath: str
    tags: list


@dataclass
class EmojiCategory:
    name: str
    emojis: list
