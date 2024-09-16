import socket
import selectors
from typing import List
from src.data.stone_type import StoneType
from src.data.inventory import Inventory
from src.goap.planner import Planner
from src.goap.worldstate import WorldState
from src.goap.action import Action
from src.goap.goal import Goal
from src.utils.logger import Logger
from src.broadcast.encryption.encrypt_data import encrypt_data
from src.loop.read.check_commands.check_fork import execute_new_program
from typing import Callable


class Player:
    def __init__(
            self,
            port: int,
            team: str,
            machine: str,
            actions: List[Action],
            forced_actions: List[Action],
            goals: List[Goal],
            mode: str,
            interpret_broadcast_function: Callable[[int, dict, 'Player'], None],
    ):
        self.port = port
        self.team = team
        self.machine = machine
        self.mode = mode

        self.interpret_broadcast_function = interpret_broadcast_function

        self.actions = actions
        self.forced_actions = forced_actions
        self.goals = goals
        self.planner = Planner(self.actions)
        self.world_state = WorldState()

        self.inventory = Inventory()

        self.client_socket: socket.socket
        self.socket_closed = False
        self.selectors = selectors.DefaultSelector()
        self.read_buffer = ""
        self.write_buffer: List = []
        self.temp_write_buffer: List = []
        self.sent_command_list: List = []

    def connect_to_server(self):
        try:
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.setblocking(False)
            self.client_socket.connect_ex((self.machine, self.port))
            self.selectors.register(self.client_socket, selectors.EVENT_READ | selectors.EVENT_WRITE)
            Logger.log(ID="connected", message="Connected to server successfully!")
        except Exception as e:
            Logger.log(ID="error", message=f"Error: {e}")

    def send_command(self, command: str):
        if len(self.write_buffer) < 10:
            self.write_buffer.append(command)
        else:
            self.temp_write_buffer.append(command)

    def send_next_command(self):
        if self.write_buffer and len(self.sent_command_list) < 10:
            next_command = self.write_buffer.pop(0)
            try:
                self.client_socket.sendall((next_command + "\n").encode('utf-8'))
                Logger.log(ID="comm_to_server", message=f"Sent: {next_command}")
                self.sent_command_list.append(next_command)
                if self.temp_write_buffer:
                    self.write_buffer.append(self.temp_write_buffer.pop(0))
            except Exception as e:
                Logger.log(ID="error", message=f"Write error: {e}")

    def receive_response(self):
        try:
            while True:
                data = self.client_socket.recv(4096).decode("utf-8")
                if not data:
                    Logger.log(ID="comm_from_server", message="Server closed the connection.")
                    self.close_connection()
                    return

                Logger.log(ID="comm_from_server", message=f"Received: {data}")
                self.read_buffer += data
        except BlockingIOError:
            return
        except socket.error as e:
            Logger.log(ID="error", message=f"Read error: {e}")
            if e.errno == 104:
                raise
        except Exception as e:
            Logger.log(ID="error", message=f"Read error: {e}")

    def close_connection(self):
        if self.selectors:
            self.selectors.unregister(self.client_socket)
        if self.client_socket:
            self.client_socket.close()
            self.socket_closed = True
            Logger.log(message="Connection closed.")

    def move(self):
        self.send("Forward")
        self.world_state.set("tiles", [])

    def turn_right(self):
        self.send("Right")
        self.world_state.set("tiles", [])

    def turn_left(self):
        self.send("Left")
        self.world_state.set("tiles", [])

    def look_around(self):
        self.send("Look")

    def check_inventory(self):
        self.send("Inventory")

    def broadcast(self, data: dict):
        encrypted_message = encrypt_data(data, self.team)
        self.send(f"Broadcast {encrypted_message}")

    def broadcast_specific(self, data: dict, team: str):
        encrypted_message = encrypt_data(data, team)
        self.send(f"Broadcast {encrypted_message}")

    def get_unused_slots(self):
        self.send("Connect_nbr")

    def fork(self):
        if self.world_state.get("fork_lay_egg"):
            Logger.log(ID="debug", message=f"Player forked")
            self.send("Fork")
        else:
            execute_new_program()

    def eject(self):
        self.send("Eject")

    def take_object(self, object_type: str):
        Logger.log(ID="debug", message=f"Taking the object of type: {object_type}")
        self.send(f"Take {object_type}")

    def set_object_down(self, object_type: str):
        Logger.log(ID="debug", message=f"Dropping the object of type: {object_type}")
        self.send(f"Set {object_type}")
        if object_type == "food":
            self.inventory.food -= 1
        else:
            self.inventory.stones.decrease_amount_by(StoneType.from_str(object_type))

    def start_incantation(self):
        self.send("Incantation")
        self.world_state.set("started_incantation", False)

    def send(self, command: str):
        try:
            if not self.client_socket:
                self.connect_to_server()
            self.send_command(command)
        except Exception as e:
            Logger.log(ID="error", message=f"Error: {e}")

        Logger.log(ID="comm_to_server", message=f"Adding command to the queue: {command}")
