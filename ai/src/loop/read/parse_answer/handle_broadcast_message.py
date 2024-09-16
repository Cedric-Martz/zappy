from src.player.player import Player
from src.utils.logger import Logger
from typing import Tuple
from src.broadcast.encryption.decrypt_data import decrypt_data


def parse_broadcast_message(broadcast: str) -> Tuple[int, str]:
    try:
        if not broadcast.startswith("message"):
            raise ValueError("Invalid broadcast format")

        parts = broadcast.split(", ", 1)
        if len(parts) != 2:
            raise ValueError("Invalid broadcast format")

        direction_str, message = parts
        direction = int(direction_str.split()[1])
        if not (0 <= direction <= 8):
            raise ValueError("Invalid direction value")

        return direction, message
    except Exception as e:
        Logger.log(ID="error", message=f"Error parsing broadcast message: {e}")
        return -1, ""


def handle_broadcast_message(player: Player, broadcast: str):
    direction, encrypted_message = parse_broadcast_message(broadcast)
    if direction == -1:
        return

    try:
        decrypted_message = decrypt_data(encrypted_message, player.team)
        player.interpret_broadcast_function(direction, decrypted_message, player)
    except Exception as e:
        Logger.log(ID="error", message=f"Error decrypting message: {e}")
        if player.mode == "evil":
            if not player.world_state.get("already_set_enemy_message") and player.world_state.get("currently_producing_food"):
                player.world_state.set("already_set_enemy_message", True)
                player.world_state.set("enemy_message", encrypted_message)
            if direction == 0:
                player.eject()
        return
