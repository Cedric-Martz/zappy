# Zappy Project

## Introduction

The Zappy project is developed as part of our curriculum at Epitech. It is a multiplayer network game where several teams of artificial intelligences compete for dominance in a virtual world. The project consists of three main parts: the server, the graphical user interface (GUI), and the artificial intelligence (AI).

## Project objectives

- **Server**: Manages the virtual world and handles communications between different entities (AI and GUI).
- **Graphical User Interface (GUI)**: Provides real-time visualization of the virtual world and AI actions.
- **Artificial Intelligence (AI)**: Develops strategies and behaviors of automated players in the virtual world.

## Team allocation

To successfully complete this project, we divided our group into three sub-teams, each responsible for a specific part of the project.

- **AI Team**:
  - [Augustin Grosnon](https://github.com/augustin-grosnon)
  - [Cédric Martz](https://github.com/Cedric-Martz/)

- **GUI Team**:
  - [Florent Guittré](https://github.com/milimarg)
  - [Corentin Metz-Dubois](https://github.com/KORV3NT)
  - [Lucas Scheidecker](https://github.com/Gazolina666)

- **Server Team**:
  - [Noé Tritsch](https://github.com/NeonMagique)
  - [Annita Rasoanaivo](https://github.com/Annita23)

## Project elements

Each part of the project has its own documentation. For detailed understanding of each component, please refer to the specific documentation:

- [AI Documentation](https://github.com/EpitechPromo2027/B-YEP-400-STG-4-1-zappy-augustin.grosnon/blob/main/ai/README.md)
- [GUI Documentation](https://github.com/EpitechPromo2027/B-YEP-400-STG-4-1-zappy-augustin.grosnon/blob/main/gui/README.md)
- [Server Documentation](https://github.com/EpitechPromo2027/B-YEP-400-STG-4-1-zappy-augustin.grosnon/blob/main/server/README.md)

### AI

The AI component is responsible for developing the strategies and behaviors of the automated players in the virtual world. This includes:

- **Vision**: How the AI perceives the virtual environment.
- **Decision Making**: The logic behind the AI's actions.
- **Communication**: Interaction between AI players.

### GUI

The GUI component provides a real-time visualization of the virtual world and the actions of the AIs. This includes:

- **Rendering**: Visual representation of the game state.
- **User Interaction**: Controls and feedback for the user.

### Server

The server component manages the virtual world and handles communications between different entities. This includes:

- **World Management**: Keeping track of game state and environment.
- **Networking**: Ensuring smooth communication between the server, AI clients, and GUI clients.

## Build instructions

To build the project, please follow these steps:

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/EpitechPromo2027/B-YEP-400-STG-4-1-zappy-augustin.grosnon.git
    cd B-YEP-400-STG-4-1-zappy-augustin.grosnon
    ```

2. **Install Dependencies**:
    - **GUI**: Ensure you have [Raylib](https://www.raylib.com/) installed.

3. **Build the Project**:

    ```bash
    make
    ```

4. **Run the Project**:
  For example, you can run each binary as follows:

- Start the server:

    ```bash
    ./zappy_server -p 1234 -x 42 -y 42 -n team1 team2 team3 -c 10 -f 200
    ```

- Start the GUI:

    ```bash
    ./zappy_gui -h 0.0.0.0 -p 1234
    ```

- Run the AI:

    ```bash
    ./zappy_ai -p 1234 -n team1
    ```

## Conclusion

This document provides an overview of the Zappy project and directs to the specific documentation for each component. Each team has worked independently on their part while ensuring seamless integration for the overall functionality of the project. For any further questions or information, please refer to the respective GitHub repositories or contact the team members.
