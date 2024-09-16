from src.loop.read.parse_answer.parse_look_result import parse_look_result
from src.player.player import Player


def check_look(player: Player, message: str, executed_command: str) -> bool:
    if "Look" in executed_command:
        player.world_state.set("tiles", parse_look_result(message))
        return True
    return False
