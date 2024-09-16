from src.actions.list.base.move import build_move
from src.actions.list.base.harvest_food import build_harvest_food
from src.actions.list.base.look_around import build_look_around
from src.actions.list.base.check_inventory import build_check_inventory
from src.actions.list.base.turn import build_turn_no_useful_resource
from src.actions.list.base.fork import build_fork_food_production, build_fork_destroy_eggs
from src.actions.list.base.send_start_broadcast import build_send_start_broadcast
from src.actions.list.base.check_start_broadcast_answer import build_check_start_broadcast_answer, build_check_no_start_broadcast_answer
from src.actions.list.base.waiting_for_start_broadcast_answer import build_waiting_for_start_broadcast_answer


def get_actions():
    return [
        build_look_around(),
        build_check_inventory(),

        build_move(),
        build_turn_no_useful_resource(),

        build_harvest_food(),

        build_send_start_broadcast(),
        build_waiting_for_start_broadcast_answer(),
        build_check_start_broadcast_answer(),
        build_check_no_start_broadcast_answer(),

        build_fork_destroy_eggs(),
        build_fork_food_production(),
    ]
