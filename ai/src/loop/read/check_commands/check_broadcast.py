from src.loop.read.parse_answer.handle_broadcast_message import handle_broadcast_message
from src.player.player import Player


def check_broadcast(player: Player, message: str) -> bool:
    if "message" not in message:
        return False

    handle_broadcast_message(player, message)
    return True
