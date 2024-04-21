/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** help
*/

#include "client.h"
#include <string.h>

static void print_help_message(void)
{
    write(1, "Available commands:\n"
    "/help\n"
    "/login [\"username\"]\n"
    "/logout\n"
    "/users\n"
    "/user [\"user_uuid\"]\n"
    "/send [\"user_uuid\"] [\"message_body\"]\n"
    "/messages [\"user_uuid\"]\n"
    "/subscribe [\"team_uuid\"]\n"
    "/subscribed\n"
    "/unsubscribe [\"team_uuid\"]\n"
    "/use [\"team_uuid\"]\n"
    "/create [\"team_name\"] [\"team_description\"]\n"
    "/list\n"
    "/info [\"team_uuid\"]\n"
    "/stop\n", 301);
}

void handle_help_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 105) {
        print_help_message();
    } else {
        printf("%s\n", temp_response);
    }
    (void) client;
    (void) request;
    (void) response;
}
