/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** calcul_utils
*/

#include "server.h"

int get_value(char *string)
{
    if (!string)
        return -1;
    return atoi(string);
}

static int search_tile(double angle)
{
    for (int i = 0; i < 8; i++)
        if (angle >= tab_angle[i][0] && angle < tab_angle[i][1])
            return i + 1;
    return 0;
}

int compute_sound(vector_t sender, vector_t receiver, int direction)
{
    int dif_x = sender.x - receiver.x;
    int dif_y = sender.y - receiver.y;
    double angle = atan2(dif_x, dif_y) * 180 / _PI;
    int tile = 0;

    if (sender.x == receiver.x && sender.y == receiver.y)
        return 0;
    angle = angle < 0 ? angle + 360 : angle;
    angle = angle >= 360 ? angle - 360 : angle;
    tile = search_tile(angle);
    tile = tile + 2 * direction - 2;
    tile = tile > 8 ? tile - 8 : tile;
    return tile;
}

static size_t count_player(vector_t pos, size_t level, server_t *server)
{
    size_t nb = 0;
    int x = pos.x;
    int y = pos.y;

    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (!curr->is_identified || curr->type != AI)
            continue;
        if (curr->pos.x == x && curr->pos.y == y && level == curr->level)
            nb++;
    }
    return nb;
}

bool check_levelup_condition(vector_t pos, size_t level, server_t *server)
{
    size_t player_on_tiles = count_player(pos, level, server);
    int position = COORD_IN_MAP(pos, WIDTH);
    int lvl_idx = level - 1;

    if (player_on_tiles < levelup_condition[lvl_idx][0])
        return false;
    for (size_t i = 1; i < RESSOURCES_NB; i++)
        if (server->world.map[position][i] < levelup_condition[lvl_idx][i])
            return false;
    return true;
}
