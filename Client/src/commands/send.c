/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** send
*/

#include "client.h"
#include "logging_client.h"
#include <string.h>

void handle_send_command(client_t *client, char *request, char *response)
{
    char *temp_response = strdup(response);
    char *token = strtok(response, ":");
    int code = atoi(token);
    char *receiver_uuid = NULL;

    if (code == 500) {
        printf("%s\n", temp_response);
        return;
    }
    if (code == 502) {
        client_error_unauthorized();
        return;
    }
    strtok(request, " ");
    receiver_uuid = strtok(NULL, "\"\"");
    strtok(NULL, "\"\"");
    if (code == 503)
        client_error_unknown_user(receiver_uuid);
    (void) client;
}
