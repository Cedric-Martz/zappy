from src.data.inventory import Inventory
from src.data.stone_type import StoneType


def parse_inventory_result(look_result: str) -> Inventory:
    inventory = Inventory()

    items = look_result.strip('[]').split(',')

    for item in items:
        item = item.strip()
        if not item:
            continue

        parts = item.split()
        if len(parts) != 2:
            continue

        name, quantity = parts[0], int(parts[1])

        if name == "food":
            inventory.food = quantity
        else:
            stone_type = StoneType.from_str(name)
            inventory.stones.set_amount(stone_type, quantity)

    return inventory
