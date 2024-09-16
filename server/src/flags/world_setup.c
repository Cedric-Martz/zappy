/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** world_setup
*/

#include "server.h"

static void mix_coords(vector_t *coords, size_t width, size_t height)
{
    vector_t temp = {0};
    size_t j = 0;

    srand(time(NULL));
    for (size_t i = 0; i < width * height - 1; i++) {
        j = i + rand() / (RAND_MAX / (width * height - i) + 1);
        temp = coords[j];
        coords[j] = coords[i];
        coords[i] = temp;
    }
}

static vector_t *get_random_coords(size_t width, size_t height)
{
    vector_t *coords = smalloc(sizeof(vector_t) * width * height,
        "world_setup.c - get_random_coords");
    size_t index = 0;

    for (size_t x = 0; x < width; x++)
        for (size_t y = 0; y < height; y++) {
            coords[index].x = x;
            coords[index].y = y;
            index++;
        }
    mix_coords(coords, width, height);
    return coords;
}

static egg_t *create_one_egg(team_t *team, world_t *world)
{
    egg_t *egg = smalloc(sizeof(egg_t), "world_setup.c - create_one_egg");

    memset(egg, 0, sizeof(egg_t));
    egg->pos.x = world->randoms_coords[world->idx].x;
    egg->pos.y = world->randoms_coords[world->idx].y;
    snprintf(egg->egg_id, MAX_ID, "%ld_%s", team->next_egg_id, team->name);
    team->next_egg_id++;
    egg->next = NULL;
    world->idx++;
    if (world->idx >= world->width * world->height)
        world->idx = 0;
    return egg;
}

static info_t *init_info_struct(size_t width, size_t height)
{
    info_t *info = smalloc(sizeof(info_t), "world_setup.c - init_info_struct");

    info->points = smalloc(sizeof(vector_t) * (width * height),
        "world_setup.c - init_info_struct");
    info->active_list = smalloc(sizeof(vector_t) * (width * height),
        "world_setup.c - init_info_struct");
    info->point_counter = 0;
    info->active_counter = 0;
    return info;
}

egg_t *create_eggs(team_t *team, world_t *world)
{
    egg_t *eggs = create_one_egg(team, world);
    egg_t *tmp = eggs;

    for (size_t i = 1; i < team->slots; i++) {
        tmp->next = create_one_egg(team, world);
        tmp = tmp->next;
    }
    return eggs;
}

void init_teams(server_t *server)
{
    team_t *teams = server->world.teams;

    while (teams) {
        teams->slots = server->world.clients_limit;
        teams->eggs = create_eggs(teams, &server->world);
        teams->next_egg_id = 1;
        teams = teams->next;
    }
}

void init_world(server_t *server, size_t width, size_t height, bool reset)
{
    if (!reset) {
        server->world.map = smalloc(sizeof(size_t *) * (width * height),
            "world_setup.c - init_world");
        server->world.randoms_coords = get_random_coords(width, height);
        server->world.refill_info = init_info_struct(width, height);
    }
    for (size_t i = 0; i < width * height; i++) {
        if (!reset)
            server->world.map[i] = smalloc(sizeof(size_t) * 7,
                "world_setup.c - init_world");
        memset(server->world.map[i], 0, 7 * sizeof(size_t));
    }
    place_ressources(server);
    init_teams(server);
}
