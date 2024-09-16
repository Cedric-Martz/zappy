from src.data.stones import Stones


class ValuesByLevel:
    def __init__(self, players: int, stones: Stones):
        self.players = players
        self.stones = stones


values_by_level = {
    1: ValuesByLevel(
        players=1,
        stones=Stones(
            linemate=1
        )
    ),
    2: ValuesByLevel(
        players=2,
        stones=Stones(
            linemate=1,
            deraumere=1,
            sibur=1
        )
    ),
    3: ValuesByLevel(
        players=2,
        stones=Stones(
            linemate=2,
            sibur=1,
            phiras=2
        )
    ),
    4: ValuesByLevel(
        players=4,
        stones=Stones(
            linemate=1,
            deraumere=1,
            sibur=2,
            phiras=1
        )
    ),
    5: ValuesByLevel(
        players=4,
        stones=Stones(
            linemate=1,
            deraumere=2,
            sibur=1,
            mendiane=3
        )
    ),
    6: ValuesByLevel(
        players=6,
        stones=Stones(
            linemate=1,
            deraumere=2,
            sibur=3,
            phiras=1
        )
    ),
    7: ValuesByLevel(
        players=6,
        stones=Stones(
            linemate=2,
            deraumere=2,
            sibur=2,
            mendiane=2,
            phiras=2,
            thystame=1
        )
    )
}

full_stones_level = ValuesByLevel(
    players=6,
    stones=Stones(
        linemate=9,
        deraumere=8,
        sibur=10,
        mendiane=5,
        phiras=6,
        thystame=1
    )
)
