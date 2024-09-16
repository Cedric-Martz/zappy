from src.goap.action import Action
from src.actions.utils.check_inventory import check_inventory


def build_check_inventory():
    return Action(
        name="CheckInventory",
        cost=1,
        preconditions={
            "know_inventory": False,
        },
        effects={
            "know_inventory": True,
        },
        final_effects={
            "check_inventory": lambda world_state: check_inventory(world_state),
            "know_inventory": True,
        }
    )
