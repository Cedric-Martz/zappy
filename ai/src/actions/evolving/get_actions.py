from src.actions.list.base.move import build_move
from src.actions.list.base.harvest_food import build_harvest_food
from src.actions.list.base.look_around import build_look_around
from src.actions.list.base.check_inventory import build_check_inventory
from src.actions.list.base.harvest_action import build_harvest_action
from src.actions.list.base.base_elevate import build_base_elevate
from src.actions.list.base.turn import build_turn_no_useful_resource
from src.actions.list.base.fork import build_fork, build_fork_food_production, build_fork_destroy_eggs
from src.actions.list.base.advanced_elevate import build_advanced_elevate
from src.actions.list.base.send_start_broadcast import build_send_start_broadcast
from src.actions.list.base.check_start_broadcast_answer import build_check_start_broadcast_answer, build_check_no_start_broadcast_answer
from src.actions.list.base.wait_for_elevation import build_wait_for_elevation
from src.actions.list.base.prepare_finish import build_prepare_finish
from src.actions.list.base.vice_leader_elevate import build_vice_leader_elevate
from src.actions.list.base.waiting_for_start_broadcast_answer import build_waiting_for_start_broadcast_answer


def get_actions():
    return [
        build_look_around(),
        build_check_inventory(),

        build_move(),
        build_turn_no_useful_resource(),

        build_harvest_food(),
        build_harvest_action("linemate"),
        build_harvest_action("deraumere"),
        build_harvest_action("sibur"),
        build_harvest_action("mendiane"),
        build_harvest_action("phiras"),
        build_harvest_action("thystame"),

        build_base_elevate(),

        build_send_start_broadcast(),
        build_waiting_for_start_broadcast_answer(),
        build_check_start_broadcast_answer(),
        build_check_no_start_broadcast_answer(),

        build_fork_destroy_eggs(),
        build_fork_food_production(),
        build_fork(),

        build_prepare_finish(),

        build_vice_leader_elevate(),

        build_advanced_elevate(),
        build_wait_for_elevation(),
    ]
