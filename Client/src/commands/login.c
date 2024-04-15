/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** login
*/

#include "client.h"
#include <string.h>

void handle_login_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);
    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    char *uuid = token;
    strtok(request, " ");
    if (code == 100) {
        client_event_logged_in(uuid, strtok(request, " "));
    } else {
        printf("%s", strtok(NULL, "\0"));
    }
    (void) client;
}

void handle_logout_command(client_t *client, char *request, char *response)
{
    (void) client;
    (void) request;
    (void) response;
}
