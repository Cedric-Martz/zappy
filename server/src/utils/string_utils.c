/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** string_utils
*/

#include "server.h"

void *smalloc(size_t size, char *func)
{
    void *buffer = malloc(size);
    char *error_string = NULL;

    if (!buffer) {
        error_string = malloc(sizeof(char) * (strlen(func) + 16));
        strcpy(error_string, func);
        strcat(error_string, ": malloc failed");
        logger(error_string);
        free(error_string);
        exit(1);
    }
    return buffer;
}

int string_to_bool(char *string)
{
    if (!string)
        return 2;
    if (!strcmp(string, "false"))
        return 0;
    if (!strcmp(string, "true"))
        return 1;
    return 2;
}

int count_char_number(char *str, char c)
{
    int i = 0;
    int count = 0;

    while (str && str[i]) {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

static bool is_empty(char *str)
{
    if (!str)
        return true;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return false;
    return true;
}

char *consume(char *str, char *rejected)
{
    char *result = NULL;

    result = strtok(str, rejected);
    if (!is_empty(result))
        return result;
    return strtok(NULL, rejected);
}
