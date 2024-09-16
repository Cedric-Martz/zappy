from src.loop.read.process_received_data import process_received_data
from src.player.player import Player


def handle_read(player: Player):
    player.receive_response()
    process_received_data(player)
