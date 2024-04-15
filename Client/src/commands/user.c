/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** user
*/

#include "client.h"
#include <string.h>

void handle_users_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);
}
