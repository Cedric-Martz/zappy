from src.goap.action import Action


def build_reset_tile_info():
    return Action(
        name="Reset tile info",
        cost=0,
        preconditions={
            "know_tiles": True,
        },
        effects={},
        final_effects={
            "knew_tiles_before": True,
        }
    )
