/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** client.c
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "commands.h"
#include "events.h"


static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/create", "/use", "/subscribed",
    "/unsubscribe", "/subscribe", "/list", "/info", "/stop"
};

static const int events_code[] = {
    104,
    200,
    201
};
static void (*events_functions[])(char *response) = {
    handle_send_event,
    handle_create_200_event,
    handle_create_201_event
};

static void (*commands_functions[])
(client_t *client, char *request, char *response) = {
    handle_help_command,
    handle_login_command,
    handle_logout_command,
    handle_users_command,
    handle_user_command,
    handle_send_command,
    handle_messages_command,
    handle_create_command,
    handle_use_command,
    handle_subscribed_command,
    handle_subscribe_command,
    handle_unsubscribe_command
};

static int read_event(int file_descriptor, char *response)
{
    int bytes_read = 0;
    int code = 0;
    char *temp_response = NULL;

    bytes_read = (int) read(file_descriptor, response, MAX_CHAR_SIZE);
    if (bytes_read < 0)
        return ERROR;
    response[bytes_read - 1] = '\0';
    temp_response = strdup(response);
    code = atoi(strtok(response, ":"));
    for (int i = 0; i < 3; i++) {
        if (code == events_code[i]) {
            events_functions[i](temp_response);
            return SUCCESS;
        }
    }
    return SUCCESS;
}

static int read_input(char *request)
{
    int bytes_read = 0;

    bytes_read = (int) read(0, request, MAX_CHAR_SIZE);
    if (bytes_read < 0)
        return ERROR;
    request[bytes_read - 1] = '\r';
    request[bytes_read] = '\n';
    request[bytes_read + 1] = '\0';
    return SUCCESS;
}

static int select_input_or_event
(int file_descriptor, char *request, char *response)
{
    fd_set read_fds;
    int max_fd;

    FD_ZERO(&read_fds);
    FD_SET(file_descriptor, &read_fds);
    FD_SET(STDOUT_FILENO, &read_fds);
    max_fd = (file_descriptor > STDOUT_FILENO) ?
    file_descriptor : STDOUT_FILENO;
    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
        return ERROR;
    if (FD_ISSET(file_descriptor, &read_fds)) {
        if (read_event(file_descriptor, response) == ERROR)
            return ERROR;
        select_input_or_event(file_descriptor, request, response);
    }
    if (FD_ISSET(STDOUT_FILENO, &read_fds))
        if (read_input(request) == ERROR)
            return ERROR;
    return SUCCESS;
}

static char *get_response(int file_descriptor, char *request, char *response)
{
    int bytes_read = 0;

    if (write(file_descriptor, request, strlen(request)) < 0) {
        return NULL;
    }
    bytes_read = (int) read(file_descriptor, response, MAX_CHAR_SIZE);
    if (bytes_read < 0){
        return NULL;
    }
    response[bytes_read - 1] = '\0';
    return response;
}

static int parse_request(client_t *client, char *request, char *response)
{
    for (int i = 0; i < 12; i++) {
        if (strncmp(request, commands[i], strlen(commands[i])) == 0) {
            commands_functions[i](client, request, response);
            return SUCCESS;
        }
    }
    return SUCCESS;
}

static int client_loop(client_t *client)
{
    char request[1024];
    char response[1024];

    while (1) {
        select_input_or_event(client->sockfd, request, response);
        get_response(client->sockfd, request, response);
        if (parse_request(client, request, response) == ERROR)
            return ERROR;
    }
    close(client->sockfd);
    free(client->ip);
    free(client);
    return SUCCESS;
}

int run_client(client_t *client)
{
    client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sockfd < 0) {
        return ERROR;
    }
    client->socket_address.sin_family = AF_INET;
    client->socket_address.sin_port = client->port;
    if (connect(client->sockfd, (struct sockaddr *)&client->socket_address,
                sizeof(client->socket_address)) < 0) {
        return ERROR;
    }
    return client_loop(client);
}
