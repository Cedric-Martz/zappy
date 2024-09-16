/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** eject_players
*/

#include "server.h"

static int check_limit(int new, int offset, int limite)
{
    if (new + offset < 0)
        return limite - 1;
    if (new + offset >= limite)
        return 0;
    return new + offset;
}

static void change_curr_pos(client_t *client, client_t *curr, server_t *server)
{
    enum orientation_type dir = client->direction;
    int k = (dir + 2 > 4) ? dir - 2 : dir + 2;
    int base_x = curr->pos.x;
    int base_y = curr->pos.y;
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, "eject: %d\n", k);
    write(curr->fd, buffer, strlen(buffer));
    for (int i = 0; i < 4; i++) {
        if (client->direction != forward[i].direction)
            continue;
        curr->pos.x = check_limit(base_x, forward[i].x, WIDTH);
        curr->pos.y = check_limit(base_y, forward[i].y, HEIGHT);
        write(client->fd, GOOD, strlen(GOOD));
        break;
    }
}

static void remove_egg(team_t *team)
{
    egg_t *eggs = team->eggs;
    egg_t *prev = NULL;
    egg_t *tmp = NULL;

    while (eggs) {
        if (!eggs->dead) {
            prev = eggs;
            eggs = eggs->next;
            continue;
        }
        if (!prev)
            team->eggs = eggs->next;
        else
            prev->next = eggs->next;
        tmp = eggs;
        eggs = eggs->next;
        team->slots--;
        free(tmp);
    }
}

static void check_player(client_t *client, server_t *server, team_t *curr_team,
    bool *did_eject)
{
    for (egg_t *egg = curr_team->eggs; egg != NULL; egg = egg->next) {
        if (client->pos.x == egg->pos.x && client->pos.y == egg->pos.y) {
            egg_death(server, egg->egg_id);
            egg->dead = true;
            *did_eject = true;
        }
    }
    remove_egg(curr_team);
}

static void eggs_management(server_t *server, client_t *client,
    bool *did_eject)
{
    team_t *curr_team = server->world.teams;

    while (curr_team) {
        check_player(client, server, curr_team, did_eject);
        curr_team = curr_team->next;
    }
}

void eject_player(char *args, client_t *client, server_t *server)
{
    bool did_eject = false;

    (void)args;
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type != AI || curr->id == client->id)
            continue;
        if (curr->pos.x == client->pos.x && curr->pos.y == client->pos.y) {
            did_eject = true;
            change_curr_pos(client, curr, server);
            eggs_management(server, curr, &did_eject);
        }
    }
    eggs_management(server, client, &did_eject);
    if (!did_eject) {
        write(client->fd, BAD, strlen(BAD));
        return logger("eject_players.c - eject_player: no player to eject");
    }
    write(client->fd, GOOD, strlen(GOOD));
    player_expulsion(server, client);
}
