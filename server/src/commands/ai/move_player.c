/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** move_player
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

void go_forward(char *args, client_t *client, server_t *server)
{
    int base_x = client->pos.x;
    int base_y = client->pos.y;
    int move_x;
    int move_y;

    (void)args;
    for (int i = 0; i < 4; i++) {
        if (forward[i].direction != client->direction)
            continue;
        move_x = forward[i].x;
        move_y = forward[i].y;
        client->pos.x = check_limit(base_x, move_x, WIDTH);
        client->pos.y = check_limit(base_y, move_y, HEIGHT);
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("move_player.c - go_forward: unknow error");
}

void go_right(char *args, client_t *client, server_t *server)
{
    (void)args;
    (void)server;
    for (int i = 0; i < 4; i++) {
        if (turns[i].left != client->direction)
            continue;
        client->direction = turns[i].right;
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("move_player.c - go_right: unknow error");
}

void go_left(char *args, client_t *client, server_t *server)
{
    (void)args;
    (void)server;
    for (int i = 0; i < 4; i++) {
        if (turns[i].right != client->direction)
            continue;
        client->direction = turns[i].left;
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("move_player.c - go_left: unknow error");
}

static void take_ressource(client_t *client, size_t *tile, look_struct_t *look)
{
    for (int idx = 0; idx < RESSOURCES_NB; idx++) {
        if (!tile[idx])
            continue;
        for (size_t i = 0; i < tile[idx]; i++)
            look->nb += snprintf(look->line + look->nb, BIG_BUFFER - look->nb,
                " %s", ressources[idx]);
    }
    if (look->nb >= 50000) {
        write(client->fd, look->line, look->nb);
        look->nb = 0;
        memset(look->line, 0, sizeof(char) * BIG_BUFFER);
    }
}

static void check_player(server_t *server, client_t *client,
    look_struct_t *look)
{
    vector_t pos = look->pos;

    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (pos.x == curr->pos.x && pos.y == curr->pos.y)
            look->nb += snprintf(look->line + look->nb, BIG_BUFFER - look->nb,
                " player");
    if (look->nb >= 50000) {
        write(client->fd, look->line, look->nb);
        look->nb = 0;
        memset(look->line, 0, sizeof(char) * BIG_BUFFER);
    }
}

static void check_coords(client_t *client, server_t *server,
    look_struct_t *look)
{
    int check_coords = 0;
    int width = WIDTH;
    int height = HEIGHT;
    vector_t pos = look->pos;

    while (pos.x < 0 || pos.x >= width) {
        pos.x = pos.x >= width ? pos.x - width : pos.x;
        pos.x = pos.x < 0 ? pos.x + width : pos.x;
    }
    while (pos.y < 0 || pos.y >= height) {
        pos.y = pos.y >= height ? pos.y - height : pos.y;
        pos.y = pos.y < 0 ? pos.y + height : pos.y;
    }
    check_coords = COORD_IN_MAP(pos, width);
    check_player(server, client, look);
    take_ressource(client, server->world.map[check_coords], look);
}

static void get_tile_position(client_t *client, vector_t *pos)
{
    vector_t prev = (vector_t){pos->x, pos->y};

    switch (client->direction) {
        case N:
            *pos = (vector_t){client->pos.x + prev.x, client->pos.y - prev.y};
            break;
        case E:
            *pos = (vector_t){client->pos.x + prev.y, client->pos.y + prev.x};
            break;
        case S:
            *pos = (vector_t){client->pos.x - prev.x, client->pos.y + prev.y};
            break;
        case W:
            *pos = (vector_t){client->pos.x - prev.y, client->pos.y - prev.x};
            break;
        default:
            break;
    }
}

void look_around(char *args, client_t *client, server_t *server)
{
    look_struct_t look = {0};
    char *separator = "";
    int level = client->level;

    (void)args;
    look.nb += snprintf(look.line + look.nb, BIG_BUFFER - look.nb, "[");
    for (int height = 0; height <= level; height++) {
        for (int width = 0 - height; width <= height; width++) {
            look.nb += snprintf(look.line + look.nb, BIG_BUFFER - look.nb,
                "%s", separator);
            look.pos = (vector_t){width, height};
            get_tile_position(client, &look.pos);
            check_coords(client, server, &look);
            separator = ",";
        }
    }
    look.nb += snprintf(look.line + look.nb, BIG_BUFFER - look.nb, "]\n");
    write(client->fd, look.line, look.nb);
}
