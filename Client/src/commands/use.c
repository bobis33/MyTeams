/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** use
*/

#include <stdio.h>
#include <string.h>
#include "client.h"

void handle_use_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 500)
        printf("%s", response);
    if (code == 502)
        client_error_unauthorized();
    if (code == 506)
        printf("%s", response);
    (void) request;
    (void) client;
}