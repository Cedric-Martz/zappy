from src.player.player import Player


def check_should_gather(player: Player, data: dict, direction: int):
    if not data.get("should_gather"):
        return
    player.world_state.set("should_gather", True)
    if direction == 0:
        player.world_state.set("at_goal", True)
    else:
        player.world_state.set("gather_direction", direction)
