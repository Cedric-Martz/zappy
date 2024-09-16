/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** tab_utils
*/

#include "server.h"

int tab_len(char **tab)
{
    int i = 0;

    while (tab[i])
        i++;
    return i;
}

int last_occurence_of(char c, char *str)
{
    int last = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            last = i;
    }
    return last;
}

static bool is_rejected(char c, char *reject)
{
    for (int i = 0; reject[i]; i++)
        if (reject[i] == c)
            return true;
    return false;
}

int count_my_words(char *str, char *reject)
{
    int nb = 0;
    bool previous_was_space = true;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_rejected(str[i], reject) && previous_was_space) {
            nb++;
            previous_was_space = false;
            continue;
        }
        if (is_rejected(str[i], reject)) {
            previous_was_space = true;
            continue;
        }
    }
    if (nb == 0)
        logger("tab_utils.c - count_my_words: no words to cut");
    return nb;
}

char **split_my_args(char *str, char *rejected)
{
    int words = count_my_words(str, rejected);
    char **args = NULL;
    char *token = NULL;

    if (!words)
        return NULL;
    args = smalloc(sizeof(char *) * (words +1), "tab_utils.c - split_my_args");
    token = strtok(str, rejected);
    for (int i = 0; token; i++) {
        args[i] = strdup(token);
        token = strtok(NULL, rejected);
    }
    args[words] = NULL;
    return args;
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}
