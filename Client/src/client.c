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


static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/create", "/use", "/subscribed",
    "/unsubscribe", "/subscribe", "/list", "/info", "/stop"
};

static void (*functions[])(client_t *client, char *request, char *response) = {
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

static char *get_request(char *request)
{
    int bytes_read = (int) read(0, request, MAX_CHAR_SIZE);

    if (bytes_read < 0) {
        return NULL;
    }
    request[bytes_read - 1] = '\r';
    request[bytes_read] = '\n';
    request[bytes_read + 1] = '\0';
    return request;
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
            functions[i](client, request, response);
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
        get_request(request);
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
