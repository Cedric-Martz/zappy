from src.player.player import Player
from src.utils.logger import Logger


def check_elevate(player: Player, message: str) -> bool:
    executed_command = ""
    try:
        temp_queue = player.sent_command_list.copy()
        temp_value = temp_queue.pop(0)
        if "Incantation" not in temp_value:
            raise Exception("No incantation executed")
        executed_command = player.sent_command_list.pop(0)
    except Exception:
        executed_command = ""

    if "Current level: " in message:
        try:
            player.world_state.set("elevation_underway", False)
            level_str = message.split("Current level: ")[1].strip()
            player.world_state.set("level", int(level_str))
            Logger.log(ID="debug", message=f"Player level updated to: {player.world_state.get('level')}")
            if player.world_state.get("is_vice_leader"):
                Logger.log(ID="debug", message="Vice leader completed elevation")
                player.world_state.set("is_vice_leader", False)
                player.world_state.set("vice_leader_check", False)
                player.broadcast({"leader_should_continue_elevation": True})
        except Exception as e:
            Logger.log(ID="error", message=f"Failed to parse level from message: {e}")
        return True

    if "Incantation" in executed_command and "ko" in message:
        player.world_state.set("elevation_underway", False)
        player.world_state.set("started_incantation", False)
        return True
    return False
