/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** place_ressources
*/

#include "server.h"

static int generate_random_point(int min, int max)
{
    int tmp = min + rand() % (max - min + 1);

    return tmp;
}

static bool in_limit(vector_t p, int width, int height)
{
    if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height)
        return true;
    return false;
}

static int distance(vector_t p1, vector_t p2)
{
    double dist =
    sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));

    return (int)dist;
}

static bool is_valid_point(vector_t *points, vector_t p, int point_counter,
    int radius)
{
    for (int i = 0; i < point_counter; i++)
        if (distance(points[i], p) < radius)
            return false;
    return true;
}

static void init_function(info_t *info, int width, int height)
{
    vector_t initial_point = {0, 0};

    initial_point.x = generate_random_point(0, width - 1);
    initial_point.y = generate_random_point(0, height - 1);
    info->points[info->point_counter] = initial_point;
    info->active_list[info->active_counter] = initial_point;
    info->point_counter++;
    info->active_counter++;
}

bool create_new_point(server_t *server, info_t *info, int index)
{
    int angle = 0;
    int new_radius = 0;
    vector_t new_point;
    vector_t current_point = info->active_list[index];

    for (int i = 0; i < K_CONSTANT; i++) {
        angle = generate_random_point(0, 359);
        new_radius = generate_random_point(RADIUS, 2 * RADIUS);
        new_point.x = current_point.x + (new_radius * cos(angle));
        new_point.y = current_point.y + (new_radius * sin(angle));
        if (in_limit(new_point, WIDTH, HEIGHT) &&
        is_valid_point(info->points, new_point, info->point_counter, RADIUS)) {
            info->points[info->point_counter] = new_point;
            info->point_counter++;
            info->active_list[info->active_counter] = new_point;
            info->active_counter++;
            return true;
        }
    }
    return false;
}

void loop_function(info_t *info, double density, server_t *server, int index)
{
    bool found;
    int idx = 0;
    int nb = WIDTH * HEIGHT * density;
    int counter_ressource = 0;

    for (size_t i = 0; i < WIDTH * HEIGHT; i++)
        counter_ressource += server->world.map[i][index];
    nb -= counter_ressource;
    while (info->point_counter < nb) {
        if (info->active_counter < 1)
            init_function(info, WIDTH, HEIGHT);
        idx = rand() % info->active_counter;
        found = false;
        found = create_new_point(server, info, idx);
        if (!found) {
            info->active_counter--;
            info->active_list[idx] = info->active_list[info->active_counter];
        }
    }
    info->point_counter = nb;
}

void reset_info(info_t *info, int width, int height)
{
    memset(info->points, 0, sizeof(vector_t) * (width * height));
    memset(info->active_list, 0, sizeof(vector_t) * (width * height));
    info->point_counter = 0;
    info->active_counter = 0;
}

void place_ressources(server_t *server)
{
    info_t *info = server->world.refill_info;
    int pos = 0;

    reset_info(info, WIDTH, HEIGHT);
    server->world.refresh += 20.0;
    for (int index = 0; index < RESSOURCES_NB; index++) {
        init_function(info, WIDTH, HEIGHT);
        loop_function(info, tiles_density[index], server, index);
        for (int i = 0; i < info->point_counter; i++) {
            pos = COORD_IN_MAP(info->points[i], WIDTH);
            server->world.map[pos][index] += 1;
        }
        reset_info(info, WIDTH, HEIGHT);
    }
}
