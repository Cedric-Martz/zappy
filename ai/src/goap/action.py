from src.goap.worldstate import WorldState


class Action:
    def __init__(self, name, cost, preconditions, effects, final_effects):
        self.name = name
        self.cost = cost
        self.preconditions = preconditions
        self.effects = effects
        self.final_effects = final_effects

    def can_execute(self, world_state):
        for k, v in self.preconditions.items():
            if callable(v):
                if not v(world_state):
                    return False
            elif world_state.get(k) != v:
                return False
        return True

    def execute(self, world_state: WorldState):
        for k, v in self.effects.items():
            if callable(v):
                v(world_state)
            else:
                world_state.set(k, v)

    def execute_final(self, world_state: WorldState):
        for k, v in self.final_effects.items():
            if callable(v):
                v(world_state)
            else:
                world_state.set(k, v)
