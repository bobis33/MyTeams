/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** login
*/

#include "logging_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_100_event(char *response)
{
    char *token = strtok(response, ":");
    char *uuid = NULL;
    char *username = NULL;

    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    uuid = token;
    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    username = token;
    client_event_logged_in(uuid, username);
}

void handle_101_event(char *response)
{
    char *token = strtok(response, ":");
    char *uuid = NULL;
    char *username = NULL;

    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    uuid = token;
    token = strtok(NULL, "[\"");
    token = strtok(NULL, "\"]");
    username = token;
    client_event_logged_out(uuid, username);
}
