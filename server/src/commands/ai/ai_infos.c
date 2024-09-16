/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ai_infos
*/

#include "server.h"

void show_inventory(char *args, client_t *client, server_t *server)
{
    char inventory[MAX_BUFFER] = {0};
    size_t nb = 1;

    (void)args;
    (void)server;
    inventory[0] = '[';
    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (i)
            nb += snprintf(inventory + nb, MAX_BUFFER - nb, ", ");
        nb += snprintf(inventory + nb, MAX_BUFFER - nb,
            "%s %ld", ressources[i], client->inventory[i]);
    }
    nb += snprintf(inventory + nb, MAX_BUFFER - nb, "]\n");
    write(client->fd, inventory, nb);
}

void show_unused_slots(char *args, client_t *client, server_t *server)
{
    team_t *teams = server->world.teams;
    char buffer[MAX_BUFFER] = {0};

    (void)args;
    while (teams) {
        if (!strcmp(teams->name, client->team)) {
            snprintf(buffer, MAX_BUFFER, VALUE, teams->slots);
            write(client->fd, buffer, strlen(buffer));
            return;
        }
        teams = teams->next;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("ai_infos.c - show_unused_slots: bad team name");
}

void send_broadcast(char *args, client_t *client, server_t *server)
{
    char *message = args ? args : "";
    char buffer[BIG_BUFFER] = {0};
    int k = 0;

    write(client->fd, GOOD, strlen(GOOD));
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type != AI || curr->id == client->id)
            continue;
        k = compute_sound(client->pos, curr->pos, curr->direction);
        snprintf(buffer, BIG_BUFFER, BROADCAST, k, message);
        write(curr->fd, buffer, strlen(buffer));
        memset(buffer, 0, BIG_BUFFER);
    }
    player_broadcast(server, client, message);
}

void player_death_ai(server_t *server, client_t *client)
{
    (void)server;
    write(client->fd, DEAD, strlen(DEAD));
}
