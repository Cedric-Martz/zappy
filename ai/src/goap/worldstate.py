class WorldState:
    def __init__(self):
        self.state = {}

    def set(self, key, value):
        self.state[key] = value

    def get(self, key, default=None):
        return self.state.get(key, default)

    def contains(self, key):
        return key in self.state

    def __str__(self):
        return str(self.state)
