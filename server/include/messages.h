/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** messages
*/

#ifndef MESSAGES_H_
    #define MESSAGES_H_

    // ? connection/disconnection
    #define CONNECTED "WELCOME\n"
    #define DISCONNECTED "GOODBYE\n"

    // ? GUI
    // map_info.c
    #define MAP_SIZE "msz %ld %ld\n"
    #define TILE_CONTENT "bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n"
    #define TEAM "tna %s\n"
    // player_infos.c
    #define PLAYER_POSITION "ppo #%ld %d %d %d\n"
    #define PLAYER_LEVEL "plv #%ld %ld\n"
    #define PLAYER_INVENTORY "pin #%ld %d %d %ld %ld %ld %ld %ld %ld %ld\n"
    #define PLAYER_DEATH "pdi #%ld\n"
    // player_actions.c
    #define PLAYER_EXPULSION "pex #%ld\n"
    #define PLAYER_BROADCAST "pbc #%ld %s\n"
    #define START_INCANTATION "pic %ld %ld %ld"
    #define END_INCANTATION "pie %ld %ld %d\n"
    // ressources_actions.c
    #define RESSOURCE_DROPPING "pdr #%ld %ld\n"
    #define RESSOURCE_COLLECTING "pgt #%ld %ld\n"
    // egg_infos.c
    #define NEW_PLAYER "pnw #%ld %d %d %d %ld %s\n"
    #define PLAYER_EGG_LAYING "pfk #%ld\n"
    #define EGG_LAID "enw #%s #%ld %d %d\n"
    #define EGG_START "ens #%s %d %d\n"
    #define EGG_CONNECTION "ebo #%s\n"
    #define EGG_DEATH "edi #%s\n"
    // time_infos.c
    #define TIME_REQUEST "sgt %ld\n"
    #define TIME_CHANGE "sst %ld\n"
    #define END_GAME "seg %s\n"
    #define SERVER_MESSAGE "smg %s\n"

    // ? IA
    #define COORDS "%d %d\n"
    #define GOOD "ok\n"
    #define BAD "ko\n"
    #define VALUE "%ld\n"
    #define DEAD "dead\n"
    #define BROADCAST "message %d, %s\n"
    #define ELEVATION "Elevation underway\n"
    #define CURRENT_LEVEL "Current level: %ld\n"

    // ? user error
    #define SYNTAX_ERROR_GUI "sbp\n"
    #define BAD_COMMAND_GUI "suc\n"

#endif /* !MESSAGES_H_ */
