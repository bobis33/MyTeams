/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** /subscribe
*/

#include <stdio.h>
#include <string.h>
#include "client.h"
#include "logging_client.h"

static void parse_response(char *token, int x, message_t message)
{
    while (token != NULL) {
        token = strtok(NULL, "[]");
        if (token == NULL)
            break;
        if (token[0] == '\"')
            x++;
        if (x == 1)
            message.user_uuid = token;
        if (x == 2)
            message.timestamp = token;
        if (x == 3) {
            message.message = token;
            x = 0;
            message.timestamp++;
            message.timestamp[strlen(message.timestamp) - 1] = '\0';
            client_print_teams
            (message.user_uuid, message.timestamp, message.message);
        }
    }
}

void handle_subscribed_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 500)
        printf("%s", response);
    if (code == 502)
        client_error_unauthorized();
    if (code == 507) {
        request[strlen(request) - 3] = '\0';
        client_error_unknown_team(request + 12);
    }
    if (code == 510)
        client_error_unauthorized();
}
