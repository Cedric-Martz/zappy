from src.actions.list.forced.reset_values import build_reset_values
from src.actions.list.forced.reset_inventory import build_reset_inventory
from src.actions.list.forced.reset_tile_info import build_reset_tile_info
from src.actions.list.forced.check_start_broadcast import build_check_start_broadcast
from src.actions.list.forced.check_vice_leader import build_check_vice_leader
from src.actions.list.forced.fork_slave_drop_food import build_fork_slave_drop_food


def get_forced_actions():
    return [
        build_reset_values(),
        build_reset_inventory(),
        build_reset_tile_info(),
        build_check_start_broadcast(),
        build_check_vice_leader(),
        build_fork_slave_drop_food(),
    ]
