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

static void parse_user_list(char *response, message_t message, int x)
{
    char *token = strtok(response, "[]");

    while (token != NULL) {
        token = strtok(NULL, "[]");
        if (token == NULL)
            break;
        if (token[0] == '\"')
            x++;
        else
            continue;
        if (x == 1)
            message.timestamp = token;
        if (x == 2)
            message.user_uuid = token;
        if (x == 3) {
            x = 0;
            client_print_users(strtok(message.user_uuid, "\"\""), strtok
            (message.timestamp, "\"\""), atoi(strtok(token, "\"\"")));
        }
    }
}

static void parse_team_list(char *response, message_t message, int x)
{
    char *token = strtok(response, "[]");

    while (token != NULL) {
        token = strtok(NULL, "[]");
        if (token == NULL)
            break;
        if (token[0] == '\"')
            x++;
        else
            continue;
        if (x == 1)
            message.timestamp = token;
        if (x == 2)
            message.user_uuid = token;
        if (x == 3) {
            x = 0;
            client_print_teams(strtok(message.user_uuid, "\"\""), strtok
            (message.timestamp, "\"\""), strtok(token, "\"\""));
        }
    }
}

void handle_subscribed_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(temp_response, ":");
    message_t message;
    int x = 0;

    if (atoi(token) == 500)
        printf("%s", response);
    if (atoi(token) == 502)
        client_error_unauthorized();
    if (atoi(token) == 507) {
        request[strlen(request) - 3] = '\0';
        client_error_unknown_team(request + 12);
    }
    if (atoi(token) == 510)
        client_error_unauthorized();
    if (atoi(token) == 102)
        parse_user_list(response, message, x);
    if (atoi(token) == 108)
        parse_team_list(response, message, x);
    (void) client;
}
