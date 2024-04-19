/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** message
*/

#include "client.h"
#include <stdio.h>
#include <string.h>

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
            client_private_message_print_messages(message.user_uuid,
            atoi(message.timestamp), message.message);
        }
    }
}

void handle_messages_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);
    int x = 0;
    message_t message;

    if (code == 500)
        printf("%s", response);
    if (code == 502)
        client_error_unauthorized();
    if (code == 503) {
        request[strlen(request) - 1] = '\0';
        client_error_unknown_user(request + 10);
    }
    if (code == 106)
        parse_response(strtok(temp_response, "[]"), x, message);
    (void) client;
}
