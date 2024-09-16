from src.goap.action import Action
from src.goap.utils.create_temp_world_state import create_temp_world_state
from src.player.player import Player
from src.utils.logger import Logger


def handle_write(player: Player):
    select_action(player)
    send_player_commands(player)


def select_action(player: Player):
    if not player.world_state.get("logged_in"):
        if player.write_buffer:
            player.send_next_command()
        return

    if player.world_state.get("elevation_underway"):
        return

    if player.sent_command_list:
        return

    temp_world_state = create_temp_world_state(player.world_state)

    if plan := player.planner.plan(temp_world_state, player.goals):
        next_action_name = plan[0]
        next_action: Action = next(action for action in player.actions if action.name == next_action_name)
        Logger.log(ID="executing_action", message=f"Executing action: {next_action.name}")
        next_action.execute_final(player.world_state)

    for action in player.forced_actions:
        if action.can_execute(player.world_state):
            action.execute_final(player.world_state)


def send_player_commands(player: Player):
    if player.write_buffer:
        while player.write_buffer and len(player.sent_command_list) < 10:
            player.world_state.set("action_count", player.world_state.get("action_count") + 1)
            player.send_next_command()
