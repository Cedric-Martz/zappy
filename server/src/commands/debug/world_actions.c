/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** world_actions
*/

#include "server.h"

void set_tile(char *args, client_t *client, server_t *server)
{
    vector_t vec = { GETTER(args), GETTER(NULL) };
    int idx = get_idx_ressources(consume(NULL, " "));
    int quantity = GETTER(NULL);
    int pos = 0;

    if (idx == -1 || vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT || quantity < 0) {
        write(client->fd, BAD, strlen(BAD));
        logger("world_actions.c - set_tile: bad args");
        return;
    }
    pos = COORD_IN_MAP(vec, WIDTH);
    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (i != idx && idx != RESSOURCES_NB)
            continue;
        server->world.map[pos][i] = quantity;
    }
    write(client->fd, GOOD, strlen(GOOD));
}

void clear_tile(char *args, client_t *client, server_t *server)
{
    vector_t vec = { GETTER(args), GETTER(NULL) };
    int idx = get_idx_ressources(consume(NULL, " "));
    int pos = COORD_IN_MAP(vec, WIDTH);

    if (vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT || idx == -1) {
        write(client->fd, BAD, strlen(BAD));
        logger("world_actions.c - clear_tile: bad args");
        return;
    }
    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (i != idx && idx != RESSOURCES_NB)
            continue;
        server->world.map[pos][i] = 0;
    }
    write(client->fd, GOOD, strlen(GOOD));
}

static void add_egg(team_t *teams, egg_t *new_egg, vector_t vec)
{
    new_egg->next = teams->eggs;
    teams->eggs = new_egg;
    new_egg->pos = vec;
    snprintf(new_egg->egg_id, MAX_ID, "%ld_%s",
    teams->next_egg_id, teams->name);
    teams->next_egg_id++;
    teams->slots++;
}

void simulate_fork(char *args, client_t *client, server_t *server)
{
    char *team_name = consume(args, " ");
    vector_t vec = { GETTER(NULL), GETTER(NULL) };
    egg_t *new_egg = smalloc(sizeof(egg_t), "world_actions.c - simulate_fork");

    if (!team_name || vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT) {
        write(client->fd, BAD, strlen(BAD));
        logger("world_actions.c - simulate_fork: bad args");
        return;
    }
    for (team_t *teams = server->world.teams; teams; teams = teams->next) {
        if (!strcmp(teams->name, team_name)) {
            add_egg(teams, new_egg, vec);
            write(client->fd, GOOD, strlen(GOOD));
            return;
        }
    }
    free(new_egg);
    write(client->fd, BAD, strlen(BAD));
    logger("world_actions.c - simulate_fork: bad team");
}

void simulate_incantation(char *args, client_t *client, server_t *server)
{
    vector_t pos = { GETTER(args), GETTER(NULL) };
    int level = GETTER(NULL);

    if (pos.x < 0 || pos.x >= (int)WIDTH || level < 1 ||
        pos.y < 0 || pos.y >= (int)HEIGHT || level > 8) {
        write(client->fd, BAD, strlen(BAD));
        return logger("world_actions.c - simulate_incantation: bad args");
    }
    if (!check_levelup_condition(pos, level, server)) {
        write(client->fd, BAD, strlen(BAD));
        return logger("world_actions.c - simulate_incantation: can't levelup");
    }
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->pos.x == pos.x && curr->pos.y == pos.y &&
            (size_t)level == curr->level) {
            write(curr->fd, ELEVATION, strlen(ELEVATION));
            curr->incantation = true;
            curr->wait = 300.0;
        }
}

static bool error_broadcast(client_t *client, server_t *server, vector_t vec)
{
    if (vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT) {
        write(client->fd, BAD, strlen(BAD));
        logger("world_actions.c - simulate_broadcast: bad args");
        return false;
    }
    return true;
}

void simulate_broadcast(char *args, client_t *client, server_t *server)
{
    vector_t vec = { GETTER(args), GETTER(NULL) };
    char *message = consume(NULL, "");
    int k = 0;
    char buffer[MAX_BUFFER] = {0};

    if (!message)
        message = "";
    if (!error_broadcast(client, server, vec))
        return;
    write(client->fd, GOOD, strlen(GOOD));
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type != AI)
            continue;
        k = compute_sound(vec, curr->pos, curr->direction);
        snprintf(buffer, MAX_BUFFER, BROADCAST, k, message);
        write(curr->fd, buffer, strlen(buffer));
        memset(buffer, 0, MAX_BUFFER);
    }
}
