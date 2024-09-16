from src.player.player import Player
from src.utils.logger import Logger
from src.player.socket.socket_wrapper import SocketWrapper


def logging_in(player: Player, message: str) -> bool:
    if not player.world_state.get("welcomed") and message == "WELCOME":
        player.world_state.set("welcomed", True)
        player.send_command(player.team)
        return True

    if not player.world_state.get("logged_in"):
        try:
            if player.world_state.get("slots_available") == -1:
                if "ko" in message:
                    Logger.log(ID="error", message="Could not log in")
                    SocketWrapper.shutdown_socket()
                    exit(84)
                player.sent_command_list.pop(0)
                player.world_state.set("slots_available", int(message))
                return True
            if player.world_state.get("map_size") == (-1, -1):
                if "ko" in message:
                    Logger.log(ID="error", message="Could not log in")
                    SocketWrapper.shutdown_socket()
                    exit(84)
                (size_x, size_y) = message.split()
                player.world_state.set("map_size", (int(size_x), int(size_y)))
                player.world_state.set("logged_in", True)
                return True
        except Exception as e:
            Logger.log(ID="error", message=f"Server sent invalid coordinates while loggin in: {e}")
        return True
    return False
