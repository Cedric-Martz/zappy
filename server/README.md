# Zappy - Server

This repository contains the source code for the server part of our Zappy project implemented in C.

## Execution

To execute the server, you will need to set multiple flags:

- `-p PORT`: Specifies the port number.
- `-x width`: Specifies the width of the world.
- `-y height`: Specifies the height of the world.
- `-n name`: Specifies the name of the teams.
- `-c limit`: Specifies the limit of clients for each team.
- `-f frequency`: Specifies the frequency of updates. (optional)

## Connection

To connect to the server, you will need to use the same port (you can use, for example, telnet or nc). When connecting, you will receive a `WELCOME\n` message from the server. After that, you can choose to become a GUI client by sending `GRAPHIC` or join a team with one of the names given in the parameters and become an AI client.

## Logger

To provide the client with information about what's happening on the server (including any errors), I created a logger method to convey error information. Here is the syntax:

``` c
file.c - function: error message
```

By default, logs are written to channel 2 (error), but this can be changed in the future with admin commands.

## GUI protocol

### Resources and variables

There is a list of ressources and variable that can be use in command by the GUI client or in response from the server, here is the list:

| Symbol |              Meaning                |
|--------|-------------------------------------|
| X      | Width or horizontal position        |
| Y      | Height or vertical position         |
| q0     | Resource 0 (food) quantity          |
| q1     | Resource 1 (linemate) quantity      |
| q2     | Resource 2 (deraumere) quantity     |
| q3     | Resource 3 (sibur) quantity         |
| q4     | Resource 4 (mendiane) quantity      |
| q5     | Resource 5 (phiras) quantity        |
| q6     | Resource 6 (thystame) quantity      |
| id     | Player id                           |
| O      | Orientation: 1(N), 2(E), 3(S), 4(W) |
| L      | Player or incantation level         |
| e      | Egg id                              |
| T      | Time unit                           |
| N      | Name of the team                    |
| R      | Incantation result                  |
| M      | Message                             |
| i      | Resource number (example: food == 0)|

### Server responses and commands - GUI

To communicate with the server, you can use the following commands to get information about the current world:

|   Command   |         Description        |         Server response             |
|-------------|----------------------------|-------------------------------------|
| `help\n`    | See all available commands | help message                        |
| `msz\n`     | Map size                   | `msz X Y\n`                         |
| `bct X Y\n` | Content of a tile          | `bct X Y q0 q1 q2 q3 q4 q5 q6\n`    |
| `mct\n`     | Tiles content of the map   | `bct * n_tiles`                     |
| `tna\n`     | Names of all the teams     | `tna NAME\n * n_teams`              |
| `ppo #id\n` | Show player's position     | `ppo #id X Y O\n`                   |
| `plv #id\n` | Show player's level        | `plv #id L\n`                       |
| `pin\n`     | Show player's inventory    | `pin #id X Y q0 q1 q2 q3 q4 q5 q6\n`|
| `sgt\n`     | Show time unit             | `sgt T\n`                           |
| `sst\n`     | Modify time unit           | `sst T\n`                           |

**(X and Y for `pin` is not used)**

You will also automatically receive some calls from the server when an AI performs an action. Here are all the possible actions:

|              Server Messages                |                   Description                    |
|---------------------------------------------|--------------------------------------------------|
| `pnw #id X Y O L N\n`                       | Connection of a new player                       |
| `pex #id\n`                                 | Expulsion                                        |
| `pbc #id M\n`                               | Broadcast                                        |
| `pic X Y L #id #id . . . \n`                | Start of an incantation (by the first player)    |
| `pie X Y R\n`                               | End of an incantation                            |
| `pfk #id\n`                                 | Egg laying by the player                         |
| `pdr #id i\n`                               | Resource dropping                                |
| `pgt #id i\n`                               | Resource collecting                              |
| `pdi #id\n`                                 | Death of a player                                |
| `enw #e #id X Y\n`                          | An egg was laid by a player                      |
| `ens #e X Y\n`                              | An egg was created at the start     (NEW)        |
| `ebo #e\n`                                  | Player connection for an egg                     |
| `edi #e\n`                                  | Death of an egg                                  |
| `seg N\n`                                   | End of game                                      |
| `smg M\n`                                   | Message from the server                          |
| `suc\n`                                     | Unknown command                                  |
| `sbp\n`                                     | Command parameter                                |

## AI protocol

### Time limit

When executing an action, the client will need to wait a certain amount of time depending on the action. This time is regulated by the frequency (freq) that represents 1 / freq (in seconds).

For example, if the time is 7/f and f = 1, the player will need to wait 7 seconds.

### Server responses and commands - AI

As an AI client, to communicate with the server, you can use the following commands to interact with your player:

|        Command         |        Description         | Time Limit |       Server Response         |
|------------------------|----------------------------|------------|-------------------------------|
| `Help\n`               | See all available commands |            | help message                  |
| `Forward\n`            | Move up one tile           |     7/f    | `ok\n`                        |
| `Right\n`              | Turn 90° right             |     7/f    | `ok\n`                        |
| `Left\n`               | Turn 90° left              |     7/f    | `ok\n`                        |
| `Look\n`               | Look around                |     7/f    | `[tile1, tile2, ... ]\n`      |
| `Inventory\n`          | Show player inventory      |     1/f    | `[food n, linemate n, ...]\n` |
| `Broadcast text\n`     | Broadcast a message        |     7/f    | `ok\n`                        |
| `Connect_nbr\n`        | Unused team slots          |     7/f    | `value\n`                     |
| `Fork\n`               | Fork a player              |    42/f    | `ok\n`                        |
| `Eject\n`              | Eject players from tile    |     7/f    | `ok\n` or `ko\n`              |
|                        | Death of a player          |            | `dead\n`                      |
| `Take resource_idx\n`  | Take a resource            |     7/f    | `ok\n` or `ko\n`              |
| `Set resource_idx\n`   | Drop a resource            |     7/f    | `ok\n` or `ko\n`              |
| `Incantation\n`        | Start level up             |   300/f    | See description below         |

When starting an Incantation, the server checks if the player has all the resources and other players required to level up. If everything is in order, the server sends `Elevation underway\n` to the client. After that, it waits for 300/f seconds. If at the end of this period the player can still level up, the server sends `Current level: k\n`. If any step fails, the server sends `ko\n`.

## ADMIN protocol

To add some options, I have decided to implement admin commands to change some information about the simulation in real time. To perform admin commands, you need to `/login password` before executing any other admin commands.

The password is very strong and difficult to guess, but here’s a hint: I love cats.

Here is a list of variables that can be used in commands by the admin client:

|   Symbol   |                          Meaning                         |
|------------|----------------------------------------------------------|
| x          | X position on the map                                    |
| y          | Y position on the map                                    |
| player_id  | ID of the player                                         |
| msg        | Message to be sent                                       |
| resource   | Resource to be used (e.g., `food`, `linemate`, or `all`) |
| quantity   | Quantity of the element to be used                       |
| team_name  | Name of a team                                           |
| true/false | Should be `true` or `false`                              |
| level      | Level to be defined                                      |

And here is all the commands:

|                   Command                    |                        Description                         |       Server Response        |
|----------------------------------------------|------------------------------------------------------------|------------------------------|
| `/clients player_id*`                        | List all connected clients or one precise                  | List of clients  or `ko\n`   |
| `/send_ais msg`                              | Send a message to all AIs                                  | `ok\n` or `ko\n`             |
| `/send_guis msg`                             | Send a message to all GUIs                                 | `ok\n` or `ko\n`             |
| `/set_inventory player_id resource quantity` | Set the quantity of a given resource in the inventory      | `ok\n` or `ko\n`             |
| `/tp player_id x y`                          | Teleport a player to a tile                                | `ok\n` or `ko\n`             |
| `/kill player_id`                            | Kill a player                                              | `ok\n` or `ko\n`             |
| `/set_level player_id level`                 | Set the level of a player                                  | `ok\n` or `ko\n`             |
| `/quit`                                      | Stop the server                                            | `ok\n`                       |
| `/clear`                                     | Clear the shell                                            | `ok\n`                       |
| `/pause`                                     | Pause the event loop                                       | `ok\n`                       |
| `/play`                                      | Start the event loop                                       | `ok\n`                       |
| `/restart`                                   | Restart the world                                          | `ok\n`                       |
| `/set_teams_slots team_name quantity`        | Change the number of available slots for a team            | `ok\n` or `ko\n`             |
| `/set_freq value`                            | Change the refresh rate                                    | `ok\n` or `ko\n`             |
| `/no_refill true/false`                      | Enable/disable world refill                                | `ok\n` or `ko\n`             |
| `/no_food true/false`                        | Enable/disable food management                             | `ok\n` or `ko\n`             |
| `/set_tile x y resource quantity`            | Set the quantity of a resource on a tile                   | `ok\n` or `ko\n`             |
| `/clear_tile x y resource`                   | Clear a resource on a tile                                 | `ok\n` or `ko\n`             |
| `/fork team_name x y`                        | Create a new "egg" for a team at the given coordinates     | `ok\n` or `ko\n`             |
| `/incantate x y level`                       | Simulate an incantation of the given level at the position | `ok\n` or `ko\n`             |
| `/broadcast x y msg*`                        | Simulate a broadcast from the given coordinates            | `ok\n` or `ko\n`             |
| `/set_logger_output filename`                | Change the output channel                                  | `ok\n`                       |

Note: Commands marked with `*` have optional arguments.

## Special information

For each command, the size limit is MAX_BUFFER (4098), and for some listed below, the limit is BIG_BUFFER (65535):

- When a GRAPHIC client connects, to get all the players and all the eggs on the world
- For a `Broadcast` command from an AI client
- For the `Look` command from an AI client
- For the `mct` command from a GRAPHIC client
- For server messages, but in this case, the server never sends any
