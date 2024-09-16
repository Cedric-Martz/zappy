import selectors
from src.loop.read.read import handle_read
from src.loop.write.write import handle_write
from src.player.player import Player
from src.player.evil.actions import handle_evil_actions


def loop(player: Player):
    while not player.socket_closed:
        handle_evil_actions(player)
        events = player.selectors.select(timeout=None)
        for key, mask in events:
            if key.fileobj == player.client_socket:
                if mask & selectors.EVENT_READ:
                    handle_read(player)
                if not player.world_state.get("alive"):
                    break;
                if mask & selectors.EVENT_WRITE and player.world_state.get("welcomed"):
                    handle_write(player)
