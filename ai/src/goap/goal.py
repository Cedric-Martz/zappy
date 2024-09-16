from src.goap.worldstate import WorldState


class Goal:
    def __init__(self, name: str, priority: int, conditions: WorldState):
        self.name = name
        self.priority = priority
        self.conditions = conditions

    def is_satisfied(self, world_state):
        for k, v in self.conditions.items():
            if callable(v):
                if not v(world_state):
                    return False
            elif world_state.get(k) != v:
                return False
        return True
