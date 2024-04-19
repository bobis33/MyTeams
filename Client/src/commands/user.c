/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** user
*/

#include "client.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *get_name(char *token)
{
    char *user_name = NULL;

    token = strtok(NULL, "[]");
    if (token == NULL)
        return NULL;
    user_name = token;
    user_name = user_name + 1;
    user_name[strlen(user_name) - 1] = '\0';
    return user_name;
}

static char *get_uuid(char *token)
{
    char *user_uuid = NULL;

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
        if (user_name == NULL)
            break;
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

static void user_handle_other_cases(int code, char *request)
{
    if (code == 500)
        printf("%s", strtok(NULL, "\0"));
    if (code == 502)
        client_error_unauthorized();
    if (code == 503) {
        request = request + 7;
        request[strlen(request) - 3] = '\0';
        client_error_unknown_user(request);
    }
}

void user_handle_main_case(int code)
{
    char *user_name = NULL;
    char *user_uuid = NULL;
    char *status_str = NULL;
    int user_status;

    if (code == 103) {
        strtok(NULL, " ");
        strtok(NULL, " ");
        user_name = strtok(NULL, "[]") + 1;
        user_name[strlen(user_name) - 1] = '\0';
        user_uuid = strtok(NULL, "[]") + 1;
        user_uuid[strlen(user_uuid) - 1] = '\0';
        strtok(NULL, "[");
        status_str = strtok(NULL, "[]") + 1;
        status_str[strlen(status_str) - 1] = '\0';
        user_status = atoi(status_str);
        client_print_user(user_uuid, user_name, user_status);
    }
}

void handle_user_command(client_t *client, char *request, char *response)
{
    char *token = strtok(response, ":");
    int code = atoi(token);

    user_handle_other_cases(code, request);
    user_handle_main_case(code);
    (void) client;
}
