/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** logger
*/

#ifndef LOGGER_H_
    #define LOGGER_H_

enum action_logger {
    SET = 0,
    GET,
};

void set_file_output(char *args, client_t *client, server_t *server);

int output_logger(char *filename, enum action_logger action);
void logger(const char *messages);

#endif /* !LOGGER_H_ */
