/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** server_commands
*/

#include "server.h"

void quit_server(char *args, client_t *client, server_t *server)
{
    (void)args;
    (void)client;
    (void)server;
    handle_signal(false, false);
}

void clear_terminal(char *args, client_t *client, server_t *server)
{
    (void)args;
    (void)server;
    write(client->fd, CLEAR, strlen(CLEAR));
}

void pause_world(char *args, client_t *client, server_t *server)
{
    (void)args;
    write(client->fd, GOOD, strlen(GOOD));
    server->stop = true;
}

void play_world(char *args, client_t *client, server_t *server)
{
    (void)args;
    write(client->fd, GOOD, strlen(GOOD));
    server->stop = false;
}

void restart_world(char *args, client_t *client, server_t *server)
{
    team_t *team = server->world.teams;

    (void)args;
    write(client->fd, GOOD, strlen(GOOD));
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next)
        if (curr->type == AI) {
            curr->dead = true;
        }
    while (team) {
        free_eggs(team, false);
        team = team->next;
    }
    server->end_game = false;
    init_world(server, WIDTH, HEIGHT, true);
}
