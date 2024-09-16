from src.goals.list.elevate import build_elevate
from src.goals.list.advanced_elevate import build_advanced_elevate
from src.goals.list.turn import build_turn
from src.goals.list.move_around import build_move_around
from src.goals.list.harvest_useful_resource import build_harvest_useful_resource
from src.goals.list.moved_towards_goal import build_moved_towards_goal
from src.goals.list.wait_for_elevation import build_wait_for_elevation
from src.goals.list.sent_start_broadcast import build_sent_start_broadcast
from src.goals.list.checked_start_broadcast_answer import build_checked_start_broadcast_answer
from src.goals.list.forked import build_forked
from src.goals.list.prepared_finish import build_prepared_finish
from src.goals.list.vice_leader_elevated import build_vice_leader_elevated
from src.goals.list.waited_for_start_broadcast_answer import build_waited_for_start_broadcast_answer


def get_goals():
    return [
        build_turn(),
        build_move_around(),
        build_elevate(),
        build_harvest_useful_resource(),
        build_moved_towards_goal(),

        build_prepared_finish(),
        build_wait_for_elevation(),

        build_sent_start_broadcast(),
        build_waited_for_start_broadcast_answer(),
        build_checked_start_broadcast_answer(),

        build_forked(),

        build_vice_leader_elevated(),
        build_advanced_elevate(),
    ]
