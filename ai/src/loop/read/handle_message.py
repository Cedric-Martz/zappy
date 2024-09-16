from src.loop.read.check_commands.elevate import check_elevate
from src.loop.read.check_commands.inventory import check_inventory
from src.loop.read.check_commands.look import check_look
from src.loop.read.check_commands.check_broadcast import check_broadcast
from src.loop.read.check_commands.logging_in import logging_in
from src.loop.read.check_commands.check_fork import check_fork
from src.player.player import Player
from src.utils.logger import Logger


def handle_message(player: Player, message: str) -> None:
    if message and message[0] == '#':
        return

    if check_broadcast(player, message):
        return

    if logging_in(player, message):
        return

    if message == "dead":
        player.world_state.set("alive", False)
        return

    if message == "Elevation underway":
        player.world_state.set("elevation_underway", True)
        return

    if check_elevate(player, message):
        return

    executed_command = player.sent_command_list.pop(0)

    Logger.log(ID="debug", message=f"Command - {executed_command} - Processing message: {message}")

    if check_look(player, message, executed_command):
        return
    if check_inventory(player, message, executed_command):
        return
    if check_fork(player, message, executed_command):
        return
