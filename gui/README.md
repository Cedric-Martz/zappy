# Zappy - GUI

This repository contains the source code for the GUI part of our Zappy project implemented in C++.

## GUI purpose

The graphical interface is used to provide a view of what is happening. This makes it possible to monitor the behaviour of AI players. More technically, we use raylib to manage the GUI.
The graphical interface communicates with the server, enabling it to update the players' layouts, actions and resources.

## Raylib dependencies

The library used in the GUI is [raylib](https://www.raylib.com/). Please ensure that you have it installed, as well as [g++](https://gcc.gnu.org/), in order to compile the code.

## Execution

To launch the GUI, you will need to set multiple flags:

- `-p PORT`: Specifies the port number of the server.
- `-h MACHINE`: Specify server IP address, localhost by default.

To launch Zappy correctly, you must first run the server, then the GUI and finally the AI.

## GUI protocol

| Symbol | Meaning                             |
|--------|-------------------------------------|
| X      | width or horizontal position        |
| Y      | height or vertical position         |
| q0     | quantity of resource 0 (food)       |
| q1     | quantity of resource 1 (linemate)   |
| q2     | quantity of resource 2 (deraumere)  |
| q3     | quantity of resource 3 (sibur)      |
| q4     | quantity of resource 4 (mendiane)   |
| q5     | quantity of resource 5 (phiras)     |
| q6     | quantity of resource 6 (thystame)   |
| n      | player number                       |
| O      | orientation: 1(N), 2(E), 3(S), 4(W) |
| L      | player or incantation level         |
| e      | egg number                          |
| T      | time unit                           |
| N      | team name                           |
| R      | incantation result                  |
| M      | message                             |
| i      | resource number                     |

| Server -> Client                          | Meaning                                      |
|-------------------------------------------|----------------------------------------------|
| `msz X Y\n`                               | map size                                     |
| `bct X Y q0 q1 q2 q3 q4 q5 q6\n`          | content of a tile                            |
| `mct\n`                                   | content of the map (all the tiles)           |
| `tna N\n * nbr_teams`                     | name of all the teams                        |
| `pnw #n X Y O L N\n`                      | connection of a new player                   |
| `ppo #n X Y O\n`                          | player's position                            |
| `plv #n L\n`                              | player's level                               |
| `pin #n X Y q0 q1 q2 q3 q4 q5 q6\n`       | player's inventory                           |
| `pex #n\n`                                | expulsion                                    |
| `pbc #n M\n`                              | broadcast                                    |
| `pic X Y L #n #n . . . \n`                | start of an incantation (by the first player)|
| `pie X Y R\n`                             | end of an incantation                        |
| `pfk #n\n`                                | egg laying by the player                     |
| `pdr #n i\n`                              | resource dropping                            |
| `pgt #n i\n`                              | resource collecting                          |
| `pdi #n\n`                                | death of a player                            |
| `enw #e #n X Y\n`                         | an egg was laid by a player                  |
| `ebo #e\n`                                | player connection for an egg                 |
| `edi #e\n`                                | death of an egg                              |
| `sgt T\n`                                 | time unit request                            |
| `sst T\n`                                 | time unit modification                       |
| `seg N\n`                                 | end of game                                  |
| `smg M\n`                                 | message from the server                      |
| `suc\n`                                   | unknown command                              |
| `sbp\n`                                   | command parameter                            |

| Client -> Server                          | Meaning                                      |
|-------------------------------------------|----------------------------------------------|
| `ppo #n\n`                                | player's position                            |
| `plv #n\n`                                | player's level                               |
| `pin #n\n`                                | player's inventory                           |
| `sgt\n`                                   | time unit request                            |
| `sst T\n`                                 | time unit modification                       |

### Compiling the code

To compile Zappy's GUI code into an executable, use the `Makefile` provided. The `Makefile` includes an `all` target which launches `zappy_gui` to create the binary.

Run the following command at root of the repository in your terminal to compile the code:

```bash
make
```

### Running the compiled executable

Once compiled, you can run the executable from the command line just like any other program. Ensure you follow the initial setup and execution steps outlined in the main section of this README.

### Example usage

Here’s an example of how to compile and run the compiled executable:

1. **Compile the code**:

   ```bash
   make
   ```

2. **Run the compiled executable**:

   ```bash
   ./zappy_gui -h MACHINE -p PORT
   ```

   Replace `PORT` and `MACHINE` with your specific server details.

## Contributors

- [Augustin Grosnon](https://github.com/augustin-grosnon)
- [Cédric Martz](https://github.com/Cedric-Martz/)
- [Florent Guittré](https://github.com/milimarg)
- [Corentin Metz-Dubois](https://github.com/KORV3NT)
- [Lucas Scheidecker](https://github.com/Gazolina666)
- [Noé Tritsch](https://github.com/NeonMagique)
- [Annita Rasoanaivo](https://github.com/Annita23)
