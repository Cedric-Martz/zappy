from src.data.stone_type import StoneType


class Stones:
    def __init__(
            self,
            linemate: int = 0,
            deraumere: int = 0,
            sibur: int = 0,
            mendiane: int = 0,
            phiras: int = 0,
            thystame: int = 0
    ):
        self.stones = {
            StoneType.LINEMATE: linemate,
            StoneType.DERAUMERE: deraumere,
            StoneType.SIBUR: sibur,
            StoneType.MENDIANE: mendiane,
            StoneType.PHIRAS: phiras,
            StoneType.THYSTAME: thystame
        }

    def get_amount(self, stone_type: StoneType) -> int:
        return self.stones.get(stone_type, 0)

    def set_amount(self, stone_type: StoneType, amount: int):
        if stone_type in self.stones:
            self.stones[stone_type] = amount

    def increase_amount_by(self, stone_type: StoneType, value: int = 1):
        if stone_type in self.stones:
            self.stones[stone_type] += value

    def decrease_amount_by(self, stone_type: StoneType, value: int = 1):
        if stone_type in self.stones:
            self.stones[stone_type] -= value

    def compare(self, other: 'Stones') -> 'Stones':
        comparison_result = Stones()
        for stone_type in self.stones:
            comparison_result.set_amount(stone_type, self.get_amount(stone_type) - other.get_amount(stone_type))
        return comparison_result

    def compare_pos(self, other: 'Stones') -> 'Stones':
        comparison_result = Stones()
        for stone_type in self.stones:
            comparison_result.set_amount(stone_type, max(self.get_amount(stone_type) - other.get_amount(stone_type), 0))
        return comparison_result

    def add(self, other: 'Stones'):
        for stone_type in self.stones:
            self.increase_amount_by(stone_type, other.get_amount(stone_type))

    def __str__(self) -> str:
        return ', '.join(f'{stone.name}: {amount}' for stone, amount in self.stones.items())

    def check_validity(self) -> bool:
        return all(count > 0 for _, count in self.stones.items())

    def check_elevation_validity(self) -> bool:
        return all(count >= 0 for _, count in self.stones.items())
