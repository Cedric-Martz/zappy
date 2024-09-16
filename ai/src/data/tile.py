from src.data.stones import Stones
from src.data.inventory import Inventory


class Tile:
    def __init__(self, stones: Stones = Stones(), food: int = 0, players=None):
        if players is None:
            players = []
        self.inventory = Inventory()
        self.inventory.food = food
        self.inventory.stones = stones
        self.players = players

    def __str__(self):
        return "Tile values - Stones: " + str(self.stones) + ", Food: " + str(self.food) + ", Players: " + str(self.players) + "."
