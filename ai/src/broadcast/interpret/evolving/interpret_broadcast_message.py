from src.utils.logger import Logger
from src.player.player import Player
from src.broadcast.interpret.list.evolving_check_anyone_is_here import check_anyone_is_here
from src.broadcast.interpret.list.check_should_gather import check_should_gather
from src.broadcast.interpret.list.info_someone_is_here import info_someone_is_here
from src.broadcast.interpret.list.info_start_food_production import info_start_food_production
from src.broadcast.interpret.list.info_is_egg_destroy_slave import info_is_egg_destroy_slave
from src.broadcast.interpret.list.check_fork_remaining import check_fork_remaining
from src.broadcast.interpret.list.check_fork_remaining import check_fork_remaining
from src.broadcast.interpret.list.check_drop_all_food import check_drop_all_food
from src.broadcast.interpret.list.check_leader_should_continue_elevation import check_leader_should_continue_elevation
from src.broadcast.interpret.list.check_players_should_continue_elevation import check_players_should_continue_elevation
from src.broadcast.interpret.list.check_set_vice_leader import check_set_vice_leader
from src.broadcast.interpret.list.check_vice_leader_action import check_vice_leader_action
from src.broadcast.interpret.list.check_set_fork_lay_egg import check_set_fork_lay_egg
from src.broadcast.interpret.list.check_take_food_amount import check_take_food_amount
from src.broadcast.interpret.list.check_player_took_food import check_player_took_food


def interpret_broadcast_message(direction: int, data: dict, player: Player):
    Logger.log(ID="broadcast_info", message=f"Received message in direction {direction}: {data}")

    check_should_gather(player, data, direction)
    info_someone_is_here(player, data)
    check_anyone_is_here(player, data)
    check_set_vice_leader(player, data)
    info_start_food_production(player, data)
    info_is_egg_destroy_slave(player, data)
    check_fork_remaining(player, data)
    check_drop_all_food(player, data)
    check_leader_should_continue_elevation(player, data)
    check_players_should_continue_elevation(player, data)
    check_vice_leader_action(player, data)
    check_set_fork_lay_egg(player, data)
    check_take_food_amount(player, data)
    check_player_took_food(player, data)
