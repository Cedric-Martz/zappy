/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** map_infos
*/

#include "server.h"

void get_map_size(char *args, client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER] = {0};

    (void)args;
    snprintf(buffer, MAX_BUFFER, MAP_SIZE, WIDTH, HEIGHT);
    write(client->fd, buffer, strlen(buffer));
}

void get_tile_info(char *args, client_t *client, server_t *server)
{
    vector_t vec = { GETTER(args), GETTER(NULL) };
    int position = 0;
    size_t *tile = NULL;
    char buffer[MAX_BUFFER] = {0};

    if (vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT) {
        write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
        logger("map_infos.c - get_tile_info: bad position");
        return;
    }
    position = COORD_IN_MAP(vec, WIDTH);
    tile = server->world.map[position];
    snprintf(buffer, MAX_BUFFER, TILE_CONTENT, (size_t)vec.x, (size_t)vec.y,
    tile[0], tile[1], tile[2],
    tile[3], tile[4], tile[5],
    tile[6]);
    write(client->fd, buffer, strlen(buffer));
    return;
}

static void check_end_mct(client_t *client, server_t *server, int *i)
{
    if ((*i) == (int)(WIDTH * HEIGHT)) {
        (*i) = 0;
        client->mctOn = false;
        write(client->fd, client->map, client->nb);
        client->nb = 0;
        memset(client->map, 0, sizeof(char) * BIG_BUFFER);
    }
}

void get_tiles_info(client_t *client, server_t *server)
{
    static int i = 0;
    int start = i + 10;
    vector_t pos = {0};
    size_t **map = server->world.map;

    for (; i < (int)(WIDTH * HEIGHT) && i < start; i++) {
        pos = (vector_t){ i % WIDTH, (i - pos.x) / HEIGHT };
        client->nb += snprintf(client->map + client->nb,
        BIG_BUFFER - client->nb, TILE_CONTENT,
        (size_t)pos.x, (size_t)pos.y, map[i][0], map[i][1],
        map[i][2], map[i][3], map[i][4], map[i][5], map[i][6]);
        if (client->nb >= 50000) {
            write(client->fd, client->map, client->nb);
            client->nb = 0;
            memset(client->map, 0, sizeof(char) * BIG_BUFFER);
        }
    }
    check_end_mct(client, server, &i);
}

void trigger_mct(char *args, client_t *client, server_t *server)
{
    (void)server;
    (void)args;
    client->mctOn = true;
}

void get_all_teams(char *args, client_t *client, server_t *server)
{
    team_t *team = server->world.teams;
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    (void)args;
    while (team) {
        nb += snprintf(buffer + nb, MAX_BUFFER - nb, TEAM, team->name);
        team = team->next;
    }
    write(client->fd, buffer, strlen(buffer));
}
