/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** help
*/

#include "client.h"
#include <string.h>

void handle_help_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);
    if (code == 105) {
        printf("Available commands:\n");
        printf("/help\n");
        printf("/login [\"username\"]\n");
        printf("/logout\n");
        printf("/users\n");
        printf("/user [\"user_uuid\"]\n");
        printf("/send [\"user_uuid\"] [\"message_body\"]\n");
        printf("/messages [\"user_uuid\"]\n");
        printf("/subscribe [\"team_uuid\"]\n");
        printf("/subscribed\n");
        printf("/unsubscribe [\"team_uuid\"]\n");
        printf("/use [\"team_uuid\"]\n");
        printf("/create [\"team_name\"] [\"team_description\"]\n");
        printf("/list\n");
        printf("/info [\"team_uuid\"]\n");
        printf("/stop\n");
    } else {
        printf("%s", strtok(NULL, "\0"));
    }
    (void) client;
    (void) request;
    (void) response;
}
