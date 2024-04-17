/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** user
*/

#include "client.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void handle_user_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);
    char *arg;

    (void) client;
    (void) request;
    (void) arg;
    (void) code;
}

static char *get_name(char *token)
{
    char *user_name;

    token = strtok(NULL, "[]");
    user_name = token;
    user_name = user_name + 1;
    user_name[strlen(user_name) - 1] = '\0';
    return user_name;
}

static char *get_uuid(char *token)
{
    char *user_uuid;

    token = strtok(NULL, "[]");
    token = strtok(NULL, "[]");
    if (token == NULL)
        return NULL;
    user_uuid = token;
    user_uuid = user_uuid + 1;
    user_uuid[strlen(user_uuid) - 1] = '\0';
    return user_uuid;
}

static int get_status(char *token)
{
    token = strtok(NULL, "[]");
    token = strtok(NULL, "[]");
    token = token + 1;
    token[strlen(token) - 1] = '\0';
    return atoi(token);
}

static void call_all_users(char *token)
{
    char *user_name;
    char *user_uuid;
    int user_status;

    while (true) {
        user_name = get_name(token);
        user_uuid = get_uuid(token);
        if (user_uuid == NULL)
            break;
        user_status = get_status(token);
        client_print_users(user_uuid, user_name, user_status);
        token = strtok(NULL, "[]");
    }
}

void handle_users_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);

    if (code == 102) {
        strtok(NULL, "[");
        call_all_users(token);
    } else if (code == 502) {
        client_error_unauthorized();
    } else {
        printf("%s", strtok(NULL, "\0"));
    }
    (void) client;
    (void) request;
}
