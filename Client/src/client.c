/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** client.c
*/

#include <stdio.h>
#include <string.h>

#include "client.h"
#include "commands.h"


static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info", "/stop"
};

static void (*functions[])(client_t *client, char *request, char *response) = {
    handle_help_command,
    handle_login_command,
    handle_logout_command
};

static char *get_request(void)
{
    char *request = malloc(sizeof(char) * MAX_CHAR_SIZE);
    if (read(0, request, MAX_CHAR_SIZE) < 0) {
        perror("read");
        return NULL;
    }
    return request;
}

static char *get_response(int file_descriptor, char *request)
{
    char *buffer = malloc(sizeof(char) * MAX_CHAR_SIZE);
    request[strcspn(request, "\0")] = '\n';
    if (write(file_descriptor, request, strlen(request)) < 0) {
        perror("write");
        return NULL;
    }
    if (read(file_descriptor, buffer, MAX_CHAR_SIZE) < 0){
        perror("read");
        return NULL;
    }
    buffer[strlen(buffer)] = '\0';
    return buffer;
}

static int parse_request(char *request, char *response)
{
    char *token = strtok(request, " ");
    if (token != NULL) {
        for (int i = 0; i < 3; i++) {
            if (strncmp(token, commands[i], strlen(commands[i])) == 0) {
                functions[i](NULL, request, response);
            }
        }
    }
    return SUCCESS;
}

static int client_loop(client_t *client)
{
    char *request = NULL;
    char *response = NULL;
    while (1) {
        request = get_request();
        if (!request)
            return ERROR;
        response = get_response(client->sockfd, request);
        if (!response)
            return ERROR;
        printf("%s", response);
        if (parse_request(request, response) == ERROR)
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
        perror("socket");
        return ERROR;
    }
    client->socket_address.sin_family = AF_INET;
    client->socket_address.sin_port = client->port;
    if (connect(client->sockfd, (struct sockaddr *)&client->socket_address,
                sizeof(client->socket_address)) < 0) {
        perror("connect");
        return ERROR;
    }
    return client_loop(client);
}
