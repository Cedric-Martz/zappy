/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** choose_type
*/

#include "server.h"

static void take_eggs(client_t *client, team_t *team, server_t *server)
{
    char value[MAX_BUFFER] = {0};
    char coords[MAX_BUFFER] = {0};
    egg_t *prev = team->eggs;

    client->pos.x = prev->pos.x;
    client->pos.y = prev->pos.y;
    team->eggs = prev->next;
    snprintf(value, MAX_BUFFER, VALUE, team->slots);
    snprintf(coords, MAX_BUFFER, COORDS,
    (int)WIDTH, (int)HEIGHT);
    write(client->fd, value, strlen(value));
    write(client->fd, coords, strlen(coords));
    egg_connection(server, client, prev->egg_id);
    free(prev);
}

static void join_team(team_t *team, client_t *client, server_t *server)
{
    static size_t id = 1;

    team->slots--;
    client->id = id;
    id++;
    client->inventory[0] = 10;
    client->eat = 0.0;
    client->type = AI;
    client->direction = (rand() % 4) + 1;
    client->level = 1;
    strcpy(client->team, team->name);
    take_eggs(client, team, server);
}

static bool try_join_team(char *team_name, client_t *client, server_t *server)
{
    team_t *teams = server->world.teams;

    while (teams) {
        if (strcmp(teams->name, team_name) != 0) {
            teams = teams->next;
            continue;
        }
        if (!teams->slots) {
            logger("choose_type.c - try_join_team: no slots available");
            return false;
        }
        join_team(teams, client, server);
        return true;
    }
    logger("choose_type.c - try_join_team: bad team name");
    return false;
}

void join_graphic(client_t *client, server_t *server)
{
    char buffer[BIG_BUFFER] = {0};
    int nb = 0;

    client->type = GUI;
    client->is_identified = true;
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type == AI) {
            nb += snprintf(buffer + nb, BIG_BUFFER - nb, NEW_PLAYER, curr->id,
            curr->pos.x, curr->pos.y, curr->direction,
            curr->level, curr->team);
        }
    }
    for (team_t *team = server->world.teams; team; team = team->next) {
        for (egg_t *egg = team->eggs; egg; egg = egg->next) {
            nb += snprintf(buffer + nb, BIG_BUFFER - nb, EGG_START,
            egg->egg_id, egg->pos.x, egg->pos.y);
        }
    }
    write(client->fd, buffer, nb);
}

void choose_type(char *command, client_t *client, server_t *server)
{
    for (int i = 0; i < TYPE_NB; i++) {
        if (!strcmp(command, type_tab[i].command)) {
            type_tab[i].function(client, server);
            return;
        }
    }
    if (!try_join_team(command, client, server)) {
        write(client->fd, BAD, strlen(BAD));
        return;
    }
    client->is_identified = true;
    return;
}
