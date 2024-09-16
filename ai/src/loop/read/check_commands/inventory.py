from src.loop.read.parse_answer.parse_inventory_result import parse_inventory_result
from src.player.player import Player


def check_inventory(player: Player, message: str, executed_command: str) -> bool:
    if "Inventory" in executed_command:
        player.inventory = parse_inventory_result(message)
        player.world_state.set("know_inventory", True)
        return True
    return False
