from src.actions.evolving.get_actions import get_actions as get_evolving_actions
from src.actions.evolving.get_forced_actions import get_forced_actions as get_evolving_forced_actions
from src.goals.evolving.get_goals import get_goals as get_evolving_goals
from src.actions.evil.get_actions import get_actions as get_evil_actions
from src.actions.evil.get_forced_actions import get_forced_actions as get_evil_forced_actions
from src.goals.evil.get_goals import get_goals as get_evil_goals
from src.goap.utils.evolving.build_world_state import build_world_state as build_evolving_world_state
from src.goap.utils.evil.build_world_state import build_world_state as build_evil_world_state
from src.broadcast.interpret.evolving.interpret_broadcast_message import interpret_broadcast_message as interpret_broadcast_message_evolving
from src.broadcast.interpret.evil.interpret_broadcast_message import interpret_broadcast_message as interpret_broadcast_message_evil
from src.player.player import Player
from src.player.socket.socket_wrapper import SocketWrapper


def init(args, uuid):
    mode_mappings = {
        "evolving": {
            "actions": get_evolving_actions,
            "forced_actions": get_evolving_forced_actions,
            "goals": get_evolving_goals,
            "interpret_broadcast": interpret_broadcast_message_evolving,
            "world_state": build_evolving_world_state,
        },
        "evil": {
            "actions": get_evil_actions,
            "forced_actions": get_evil_forced_actions,
            "goals": get_evil_goals,
            "interpret_broadcast": interpret_broadcast_message_evil,
            "world_state": build_evil_world_state,
        }
    }

    mode_config = mode_mappings[args.mode]

    player = Player(
        port=args.port,
        team=args.name,
        machine=args.machine,
        actions=mode_config["actions"](),
        forced_actions=mode_config["forced_actions"](),
        goals=mode_config["goals"](),
        mode=args.mode,
        interpret_broadcast_function=mode_config["interpret_broadcast"]
    )

    player.connect_to_server()

    player.inventory.food = 10
    player.world_state = mode_config["world_state"](player, uuid)
    SocketWrapper.set_socket(player.client_socket)

    return player
