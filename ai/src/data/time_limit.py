from enum import Enum


class TimeLimit(Enum):
    FORWARD = 7
    RIGHT = 7
    LEFT = 7
    LOOK = 7
    INVENTORY = 1
    BROADCAST_TEXT = 7
    CONNECT_NBR = 0
    FORK = 42
    EJECT = 7
    TAKE_OBJECT = 7
    SET_OBJECT = 7
    INCANTATION = 300

    def __int__(self) -> int:
        return self.value
