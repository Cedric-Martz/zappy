/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ai_actions
*/

#include "server.h"

static bool take_ressource(char *ressource, client_t *client, server_t *server)
{
    int position = COORD_IN_MAP(client->pos, WIDTH);

    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (strcmp(ressources[i], ressource))
            continue;
        if (!server->world.map[position][i]) {
            write(client->fd, BAD, strlen(BAD));
            logger("ai_actions.c - take_ressource: can't take this ressource");
            return true;
        }
        server->world.map[position][i]--;
        client->inventory[i]++;
        player_ressource_collecting(server, client, i);
        write(client->fd, GOOD, strlen(GOOD));
        return true;
    }
    return false;
}

void take_object(char *args, client_t *client, server_t *server)
{
    char *ressource = consume(args, " ");

    if (!ressource) {
        write(client->fd, BAD, strlen(BAD));
        logger("ai_actions.c - take_object: bad ressource");
        return;
    }
    if (take_ressource(ressource, client, server))
        return;
    write(client->fd, BAD, strlen(BAD));
    logger("ai_actions.c - take_object: bad ressource");
}

static bool drop_ressource(char *ressource, client_t *client, server_t *server)
{
    int position = COORD_IN_MAP(client->pos, WIDTH);

    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (strcmp(ressources[i], ressource))
            continue;
        if (!client->inventory[i]) {
            write(client->fd, BAD, strlen(BAD));
            logger("ai_actions.c - drop_object: can't drop this ressource");
            return true;
        }
        server->world.map[position][i]++;
        client->inventory[i]--;
        player_ressource_dropping(server, client, i);
        write(client->fd, GOOD, strlen(GOOD));
        return true;
    }
    return false;
}

void drop_object(char *args, client_t *client, server_t *server)
{
    char *ressource = consume(args, " ");

    if (!ressource) {
        write(client->fd, BAD, strlen(BAD));
        logger("ai_actions.c - take_object: bad ressource");
        return;
    }
    if (drop_ressource(ressource, client, server))
        return;
    write(client->fd, BAD, strlen(BAD));
    logger("ai_actions.c - drop_object: bad ressource");
}

void start_incancation(char *args, client_t *client, server_t *server)
{
    int x = client->pos.x;
    int y = client->pos.y;
    size_t level = client->level;

    (void)args;
    if (!check_levelup_condition(client->pos, client->level, server)) {
        write(client->fd, BAD, strlen(BAD));
        logger("ai_actions.c - start_incancation: can't start incantation");
        return;
    }
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->pos.x == x && curr->pos.y == y && level == curr->level) {
            write(curr->fd, ELEVATION, strlen(ELEVATION));
            curr->incantation = true;
            curr->wait = 300.0;
        }
    player_start_incantation(server, client);
}

static void result_incantation(client_t *client, server_t *server, bool result)
{
    vector_t pos = client->pos;
    size_t lvl = client->level;
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, CURRENT_LEVEL, client->level + 1);
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->pos.x != pos.x || curr->pos.y != pos.y || lvl != curr->level)
            continue;
        if (result) {
            curr->level++;
            write(curr->fd, buffer, strlen(buffer));
        }
        curr->incantation = false;
    }
    player_end_incantation(server, client, result);
    end_game(server, lvl + result);
}

void check_incantation(client_t *client, server_t *server)
{
    bool success = true;

    if (!check_levelup_condition(client->pos, client->level, server)) {
        write(client->fd, BAD, strlen(BAD));
        logger("ai_actions.c - check_incantation: can't end incantation");
        success = false;
    }
    result_incantation(client, server, success);
}

static void add_egg(team_t *teams, egg_t *new_egg, client_t *client)
{
    new_egg->next = teams->eggs;
    teams->eggs = new_egg;
    new_egg->pos = (vector_t){client->pos.x, client->pos.y};
    snprintf(new_egg->egg_id, MAX_ID, "%ld_%s",
    teams->next_egg_id, teams->name);
    teams->next_egg_id++;
    teams->slots++;
}

void fork_player(char *args, client_t *client, server_t *server)
{
    team_t *teams = server->world.teams;
    egg_t *new_egg = smalloc(sizeof(egg_t), "ai_actions.c - fork_player");

    (void)args;
    player_egg_laying(server, client);
    while (teams) {
        if (!strcmp(teams->name, client->team)) {
            add_egg(teams, new_egg, client);
            write(client->fd, GOOD, strlen(GOOD));
            egg_laid(server, client, new_egg->egg_id);
            return;
        }
        teams = teams->next;
    }
    free(new_egg);
    write(client->fd, BAD, strlen(BAD));
    logger("ai_actions.c - fork_player: bad team fork");
}
