from src.player.player import Player


def check_take_food_amount(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if player.world_state.get("end_player_food_taken"):
        return;
    food_to_take = data.get("take_food_amount")
    if food_to_take is None:
        return
    import sys
    for _ in range(food_to_take):
        player.take_object("food")
    player.world_state.set("end_player_food_taken", True)
    player.broadcast({"tell_leader_food_is_taken": True})
