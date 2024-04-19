/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** create
*/

#include "client.h"
#include <string.h>

void handle_create_200_event(char *response)
{
    char *uuid = NULL;
    char *name = NULL;
    char *desc = NULL;

    strtok(response, "[]");
    uuid = strtok(NULL, "[]");
    strtok(NULL, "[]");
    name = strtok(NULL, "[]");
    strtok(NULL, "[]");
    desc = strtok(NULL, "[]");
    uuid = strtok(uuid, "\"\"");
    name = strtok(name, "\"\"");
    desc = strtok(desc, "\"\"");
    client_event_team_created(uuid, name, desc);
}

void handle_create_201_event(char *response)
{
    char *uuid = NULL;
    char *name = NULL;
    char *desc = NULL;

    strtok(response, "[]");
    uuid = strtok(NULL, "[]");
    strtok(NULL, "[]");
    name = strtok(NULL, "[]");
    strtok(NULL, "[]");
    desc = strtok(NULL, "[]");
    uuid = strtok(uuid, "\"\"");
    name = strtok(name, "\"\"");
    desc = strtok(desc, "\"\"");
    client_event_channel_created(uuid, name, desc);
}
