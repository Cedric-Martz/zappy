from enum import Enum


class StoneType(Enum):
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6

    def __str__(self):
        return self.name.lower()

    @classmethod
    def from_str(cls, value: str) -> 'StoneType':
        try:
            return cls[value.upper()]
        except KeyError as e:
            raise ValueError(f"No stone type found for '{value}'") from e

    @classmethod
    def is_stone(cls, value: str) -> bool:
        try:
            _ = cls[value.upper()]
            return True
        except KeyError:
            return False
