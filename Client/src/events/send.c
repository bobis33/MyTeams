/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** send
*/

#include "client.h"
#include <string.h>

void handle_send_event(char *response)
{
    char *uuid = NULL;
    char *message = NULL;

    strtok(response, "[]");
    uuid = strtok(NULL, "[]");
    strtok(NULL, "[]");
    message = strtok(NULL, "[]");
    uuid = strtok(uuid, "\"\"");
    message = strtok(message, "\"\"");
    client_event_private_message_received(uuid, message);
}
