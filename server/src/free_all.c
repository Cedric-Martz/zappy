/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** free_all
*/

#include "server.h"

void free_clients(client_t *clients)
{
    client_t *prev = NULL;

    while (clients) {
        if (prev) {
            shutdown(prev->fd, SHUT_RDWR);
            close(prev->fd);
            free(prev);
            prev = NULL;
        }
        prev = clients;
        clients = clients->next;
    }
    if (prev) {
        shutdown(prev->fd, SHUT_RDWR);
        close(prev->fd);
        free(prev);
    }
}

void free_eggs(team_t *team, bool erase_team)
{
    egg_t *eggs = team->eggs;
    egg_t *prev = NULL;

    while (eggs) {
        if (prev) {
            free(prev);
            prev = NULL;
        }
        prev = eggs;
        eggs = eggs->next;
    }
    if (prev)
        free(prev);
    if (erase_team) {
        if (team->name)
            free(team->name);
        free(team);
    }
}

static void free_teams(team_t *teams)
{
    team_t *prev = NULL;

    while (teams) {
        if (prev) {
            free_eggs(prev, true);
            prev = NULL;
        }
        prev = teams;
        teams = teams->next;
    }
    if (prev)
        free_eggs(prev, true);
}

static void free_world(world_t world)
{
    if (world.teams)
        free_teams(world.teams);
    if (world.randoms_coords)
        free(world.randoms_coords);
    if (world.refill_info) {
        free(world.refill_info->points);
        free(world.refill_info->active_list);
        free(world.refill_info);
    }
    if (world.map) {
        for (size_t i = 0; i < world.width * world.height; i++)
            free(world.map[i]);
        free(world.map);
    }
}

static void close_client(server_t *server, client_t *client)
{
        if (client->type == AI && !server->end_game)
            player_death_gui(server, client);
        shutdown(client->fd, SHUT_RDWR);
        close(client->fd);
        free(client);
}

void remove_client(server_t *server)
{
    client_t *client = server->clients;
    client_t *prev = NULL;
    client_t *tmp = NULL;

    while (client) {
        if (!client->dead) {
            prev = client;
            client = client->next;
            continue;
        }
        if (!prev)
            server->clients = client->next;
        else
            prev->next = client->next;
        tmp = client;
        client = client->next;
        close_client(server, tmp);
    }
}

void free_all(server_t *server)
{
    if (server) {
        close(server->serv_socket);
        free_clients(server->clients);
        free_world(server->world);
        free(server);
    }
}
