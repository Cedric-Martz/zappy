# Zappy - AI

This repository contains the source code for the AI part of our Zappy project implemented in Cython.

## Execution

To launch an AI player, you will need to set multiple flags:

- `-p PORT`: Specifies the port number of the server.
- `-n NAME`: Specify the name of the team the AI player will join.
- `-h MACHINE`: (Optional) Specify server IP address, localhost by default.
- `-m [--mode] MODE`: (Optional) Select the AI mode, evolving by default.

In order to launch the AI correctly, you must first launch the server, and then you can launch the AI. However, it is recommended to launch the server first, then the GUI and finally the AI. Once all these have been launched, you can look at the GUI window and follow the progress of the AIs. If you don't specify `-m`, the mode will be default.

## AI protocol

### Time limit

When executing an action, the client will need to wait a certain amount of time depending on the action. This time is regulated by the frequency (freq) that represents 1 / freq (in seconds).

For example, if the time is 7/f and f = 1, the player will need to wait 7 seconds.

### Server responses and commands

As an AI client, to communicate with the server, you can use the following commands to interact with your player:

#### Command List

- **Help**: Lists all available commands.
  - **Usage**: `Help\n`
  - **Response**: `help`

- **Forward**: Moves the player forward by one tile.
  - **Usage**: `Forward\n`
  - **Response**: `ok\n`

- **Right**: Turns the player 90 degrees to the right.
  - **Usage**: `Right\n`
  - **Response**: `ok\n`

- **Left**: Turns the player 90 degrees to the left.
  - **Usage**: `Left\n`
  - **Response**: `ok\n`

- **Look**: Allows the player to look around and returns the content of the surrounding tiles.
  - **Usage**: `Look\n`
  - **Response**: `[tile1, tile2, ... ]\n`

- **Inventory**: Displays the player's inventory.
  - **Usage**: `Inventory\n`
  - **Response**: `[food n, linemate n, ...]\n`

- **Broadcast**: Broadcasts a  to all players.
  - **Usage**: `Broadcast text\n`
  - **Response**: `ok\n`

- **Connect_nbr**: Returns the number of unused slots in the team.
  - **Usage**: `Connect_nbr\n`
  - **Response**: `value\n`

- **Fork**: Creates a new player at the current position.
  - **Usage**: `Fork\n`
  - **Response**: `ok\n`

- **Eject**: Ejects all players on the current tile to adjacent tiles.
  - **Usage**: `Eject\n`
  - **Response**: `ok\n` or `ko\n`

- **Take**: Takes a specified resource from the current tile.
  - **Usage**: `Take resource_idx\n`
  - **Response**: `ok\n` or `ko\n`

- **Set**: Drops a specified resource on the current tile.
  - **Usage**: `Set resource_idx\n`
  - **Response**: `ok\n` or `ko\n`

- **Incantation**: Begins the process of leveling up.
  - **Usage**: `Incantation\n`
  - **Response**: See details below

#### Command Table

|        Command         |        Description         | Time Limit |       Server Response         |
|------------------------|----------------------------|------------|-------------------------------|
| `Help\n`               | See all available commands |            | help                   |
| `Forward\n`            | Move up one tile           |     7/f    | `ok\n`                        |
| `Right\n`              | Turn 90° right             |     7/f    | `ok\n`                        |
| `Left\n`               | Turn 90° left              |     7/f    | `ok\n`                        |
| `Look\n`               | Look around                |     7/f    | `[tile1, tile2, ... ]\n`      |
| `Inventory\n`          | Show player inventory      |     1/f    | `[food n, linemate n, ...]\n` |
| `Broadcast text\n`     | Broadcast a         |     7/f    | `ok\n`                        |
| `Connect_nbr\n`        | Unused team slots          |     7/f    | `value\n`                     |
| `Fork\n`               | Fork a player              |    42/f    | `ok\n`                        |
| `Eject\n`              | Eject players from tile    |     7/f    | `ok\n` or `ko\n`              |
|                        | Death of a player          |            | `dead\n`                      |
| `Take resource_idx\n`  | Take a resource            |     7/f    | `ok\n` or `ko\n`              |
| `Set resource_idx\n`   | Drop a resource            |     7/f    | `ok\n` or `ko\n`              |
| `Incantation\n`        | Start level up             |   300/f    | See description below         |

### Detailed Command Descriptions

#### Look

The `Look` command allows the player to see the content of the tiles in their immediate vicinity. The vision is in a cone shape, and the range of vision increases with the player's level. The server response is a list of the items on each tile within the cone of vision.

- **Example**: `Look\n`
- **Response**: `[food, linemate, deraumere, ...]\n`

#### Broadcast

The `Broadcast` command sends a message to all players in the game. It is transmitted directionally, and players can determine the origin of the broadcast based on the direction from which the sound is coming. Direction is a number between 1 and 8, corresponding to the direction relative to the player, starting with the direction the player is facing and winding counter-clockwise. A direction of 0 indicates that the sound comes from the player's tile.

- **Example**: `Broadcast Hello team!\n`
- **Response**: `ok\n`
- **Received message example**: `Received message in direction 6: {'check_if_anyone_is_here': True}\n`

In our implementation, messages are encrypted with a random component and a keyword based on the team's name, then serialized in base64 before being sent. This ensures that messages can only be understood by members of the same team, unless an evil AI decides to change this.

#### Incantation

The `Incantation` command is used to level up a player. The player must meet specific requirements, including having a certain number of resources and nearby players. The server first checks these requirements and responds with `Elevation underway\n` if they are met. After a delay, if the requirements are still met, the server responds with `Current level: k\n`. If any requirement is not met during the delay, the server responds with `ko\n`.

- **Example**: `Incantation\n`
- **Initial Response**: `Elevation underway\n`
- **Final Response**: `Current level: k\n` or `ko\n`

## Game goal

The goal of the AI in Zappy is to survive and collect resources to evolve to level 8. The game is won when at least 6 players from the same team reach level 8.

## JSON configuration

You can configure the logger using a JSON configuration file. This allows you to specify various settings and logger behaviors in a centralized and easy-to-edit format. The configuration file should be placed in the `config` directory and named `logger_config.json`.

### Example configuration

Below is an example of a JSON configuration file for the logger:

```json
{
    "colored": true,
    "timestamped": false,
    "timestamp_format": "%Y-%m-%d %H:%M:%S ",
    "disabled": false,
    "display_uuid": true,
    "filename_uuid": true,
    "loggers": [
        {
            "ID": "error",
            "channel": "stderr",
            "color": "RED",
            "filepath": "logs/error.log",
            "mode": "a",
            "disabled": false
        },
        {
            "ID": "goal_selected",
            "color": "GREEN"
        },
        {
            "ID": "connected",
            "color": "BACK_GREEN"
        },
        {
            "ID": "executing_action",
            "color": "BACK_CYAN"
        },
        {
            "ID": "comm_to_server",
            "color": "BLUE"
        },
        {
            "ID": "comm_from_server",
            "color": "MAGENTA"
        },
        {
            "ID": "broadcast_info",
            "filepath": "logs/broadcast_info.log"
        },
        {
            "ID": "info",
            "color": "YELLOW"
        },
        {
            "ID": "evil",
            "color": "BACK_RED"
        }
    ]
}
```

### Configuration Options

- `colored` (optional): Enables or disables colored output in the console. (`disabled` by default)
- `timestamped` (optional): Enables or disables timestamps in the log messages. (`disabled` by default)
- `timestamp_format` (optional): Specifies the format of the timestamp. (`'%Y-%m-%d %H:%M:%S '` by default)
- `disabled` (optional): Globally enables or disables logging. (`false` by default)
- `display_uuid` (optional): Option to display UUID in log messages. (`disabled` by default)
- `filename_uuid` (optional): Option to include UUID in log file names. (`disabled` by default)
- `loggers`: A list of logger configurations.

### Logger Configuration Fields

Each logger in the `loggers` array can have the following fields:

- `ID`: A unique identifier for the logger.
- `channel` (optional): The output channel for the logger (`stdout` or `stderr`). (`stdout` by default)
- `color` (optional): The color of the log messages. Valid values include color names such as `RED`, `GREEN`, `BACK_GREEN`, etc. (`white` by default)
- `filepath` (optional): The file path for the log output (if using file logging). (`disabled` by default)
- `mode` (optional): The file mode (`a` for append, `w` for write). (`a` by default)
- `disabled` (optional): Enables or disables the specific logger. (`false` by default)

#### Available colors

You can use the following colors for the `color` field in the logger configuration:

- Foreground colors:
  - `red`
  - `green`
  - `blue`
  - `cyan`
  - `magenta`
  - `yellow`
  - `white`
  - `black`

- Background colors:
  - `back_red`
  - `back_green`
  - `back_blue`
  - `back_cyan`
  - `back_magenta`
  - `back_yellow`
  - `back_white`
  - `back_black`

## Evil AI

You can launch Evil AI in teams. Evil AI will try to brute-force intercepted communications from other teams. If it succeeds, it will reply with erroneous messages, with the aim of rendering the team ineffective or even destroying it completely.

To launch an evil AI player, you will need to use the following flag:

- `-m [--mode] evil`

## Compiling the code with Nuitka

To compile the Zappy AI code into C using Nuitka, follow these steps. Compiling the code allows for faster execution and distribution, making it run efficiently as a standalone executable.

### Dependencies

Before compiling with Nuitka, ensure you have the following dependencies installed on your system:

- Python (>= 3.6)
- Nuitka

You can install Nuitka using pip:

```bash
pip install nuitka
```

### Compiling the code

To compile the Zappy AI code into a standalone executable, use the provided `Makefile`. The `Makefile` includes a target `compiled` that facilitates compiling the code using Nuitka.

Run the following command in your terminal to compile the code:

```bash
make compiled
```

This command will invoke Nuitka to compile the Python source code into C, optimizing it for faster execution. After compilation, the executable will function the same as the normal Python version of the AI.

### Running the compiled executable

Once compiled, you can run the executable from the command line just like any other program. Ensure you follow the initial setup and execution steps outlined in the main section of this README.

### Example usage

Here’s an example of how to compile and run the compiled executable:

1. **Compile the code**:

   ```bash
   make compiled
   ```

2. **Run the compiled executable**:

   ```bash
   ./zappy_ai -p PORT -n TEAMNAME [-h MACHINE] [-m MODE]
   ```

   Replace `PORT`, `TEAMNAME`, `MACHINE`, and `MODE` with your specific server details and AI configuration.

## Contributors

- [Augustin Grosnon](https://github.com/augustin-grosnon)
- [Cédric Martz](https://github.com/Cedric-Martz/)
