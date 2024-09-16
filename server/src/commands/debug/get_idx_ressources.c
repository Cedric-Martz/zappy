/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** get_idx_ressources.c
*/

#include "server.h"

int get_idx_ressources(char *ressource)
{
    if (!ressource)
        return -1;
    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (!strcmp(ressource, ressources[i]))
            return i;
    }
    if (!strcmp(ressource, "all"))
        return 7;
    return -1;
}
