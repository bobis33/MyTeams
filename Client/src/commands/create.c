/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** create
*/

#include "client.h"
#include "logging_client.h"
#include <stdio.h>
#include <string.h>

static void handle_create_team(char *request, char *temp_response, int code)
{
    char *name = NULL;
    char *description = NULL;
    char *uuid = NULL;

    if (code == 107) {
        request += 9;
        name = strdup(request);
        description = strdup(strstr(request, "\" \"") + 3);
        name[strlen(request) - strlen(strstr(request, "\" \""))] = '\0';
        description[strlen(description) - 3] = '\0';
        strtok(temp_response, "[]");
        uuid = strtok(NULL, "[]");
        uuid[strlen(uuid) - 1] = '\0';
        uuid++;
        client_print_team_created(uuid, name, description);
    }
}

static void handle_create_channel(char *request, char *temp_response, int code)
{
    char *name = NULL;
    char *description = NULL;
    char *uuid = NULL;

    request += 9;
    if (code == 109) {
        name = strdup(request);
        description = strdup(strstr(request, "\" \"") + 3);
        name[strlen(request) - strlen(strstr(request, "\" \""))] = '\0';
        description[strlen(description) - 3] = '\0';
        strtok(temp_response, "[]");
        uuid = strtok(NULL, "[]");
        uuid[strlen(uuid) - 1] = '\0';
        uuid++;
        client_print_channel_created(uuid, name, description);
    }
}

void handle_create_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 500)
        printf("%s", response);
    if (code == 502)
        client_error_unauthorized();
    if (code == 505)
        client_error_already_exist();
    if (code == 511)
        client_error_already_exist();
    handle_create_team(request, temp_response, code);
    handle_create_channel(request, temp_response, code);
    (void) client;
}
