from src.player.player import Player


def fork_slave_drop_food(player: Player):
    for _ in range(player.inventory.food - 1):
        player.set_object_down("food")
