/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** utils
*/

#include "utils.h"
#include "server.h"

#include <string.h>

char *clear_command(char *command)
{
    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == '\n' || command[i] == '\r')
            command[i] = '\0';
    return command;
}

user_t *search_user_by_name(server_t *server, char *name)
{
    for (int i = 0; i < server->usersCount; i++)
        if (strcmp(server->users[i].name, name) == 0) {
            return &server->users[i];
        }
    return NULL;
}
