/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** /subscribe
*/

#include <stdio.h>
#include <string.h>
#include "client.h"

void handle_subscribe_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 500)
        printf("%s\n", temp_response);
    if (code == 502)
        client_error_unauthorized();
    if (code == 507) {
        client_error_unknown_team(strtok(request + 12, "\"\""));
    }
    if (code == 508)
        printf("%s\n", temp_response);
    (void) client;
}
