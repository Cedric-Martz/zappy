import heapq
from typing import List, Tuple
from src.goap.action import Action
from src.goap.goal import Goal
from src.goap.utils.create_temp_world_state import create_temp_world_state
from src.goap.worldstate import WorldState
from src.utils.logger import Logger


class Planner:
    def __init__(self, actions: List[Action]):
        self.actions = actions

    def plan(self, start_state: WorldState, goals: List[Goal]):
        all_paths: List[Tuple[Goal, List[str]]] = []

        max_depth: int = 100

        for goal in goals:
            open_set: List[Tuple[int, int, 'WorldState', List[str]]] = []
            str_list: List[str] = []
            heapq.heappush(open_set, (0, id(start_state), start_state, str_list))

            current_depth = 0
            while open_set and current_depth < max_depth:
                current_depth += 1

                current_cost, _, current_state, path = heapq.heappop(open_set)

                if goal.is_satisfied(current_state):
                    Logger.log(ID="goal_selected", message=f"Goal {goal.name} satisfied with path: {path}")
                    all_paths.append((goal, path))
                    break

                for action in self.actions:
                    if action.can_execute(current_state):
                        new_state = create_temp_world_state(current_state)
                        action.execute(new_state)
                        new_path = path + [action.name]
                        new_cost = current_cost + action.cost
                        new_state_id = id(new_state)
                        heapq.heappush(open_set, (new_cost, new_state_id, new_state, new_path))

        if all_paths:
            goal, selected_path = max(all_paths, key=lambda x: x[0].priority)
            Logger.log(ID="goal_selected", message=f"Selected path: {selected_path} - goal was: {goal.name}")
            return selected_path

        Logger.log(ID="error", message=f"No path found for any of the goal")
        return []
