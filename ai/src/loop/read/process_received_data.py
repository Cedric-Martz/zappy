from src.loop.read.handle_message import handle_message
from src.player.player import Player


def process_received_data(player: Player):
    delimiter = "\n"
    while delimiter in player.read_buffer:
        message, player.read_buffer = player.read_buffer.split(delimiter, 1)
        handle_message(player, message)
