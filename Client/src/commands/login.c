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
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);
    char *uuid = NULL;

    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    uuid = token;
    if (code == 100) {
        client->user_name = strdup(request + 8);
        client->user_name[strlen(client->user_name) - 3] = '\0';
        client->uuid = strdup(uuid);
        request[strlen(request) - 1] = '\0';
        client_event_logged_in(uuid, client->user_name);
    } else {
        printf("%s\n", temp_response);
    }
}

void handle_logout_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);
    char *uuid = NULL;

    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    uuid = token;
    strtok(request, " ");
    if (code == 101) {
        client_event_logged_out(uuid, client->user_name);
    } else if (code == 502) {
        client_error_unauthorized();
    } else {
        printf("%s\n", temp_response);
    }
}
