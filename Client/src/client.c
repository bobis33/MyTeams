/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** client.c
*/

#include <string.h>

#include "client.h"

static int handle_input(int file_descriptor)
{
    char buffer[MAX_CHAR_SIZE] = {0};
    char request[MAX_CHAR_SIZE] = {0};

    if (read(0, request, MAX_CHAR_SIZE) < 0) {
        perror("read");
        return ERROR;
    }
    request[strcspn(request, "\0")] = '\n';
    if (write(file_descriptor, request, strlen(request)) < 0) {
        perror("write");
        return ERROR;
    }
    if (read(file_descriptor, buffer, MAX_CHAR_SIZE) < 0){
        perror("read");
        return ERROR;
    }
    buffer[strlen(buffer)] = '\0';
    write(1, buffer, strlen(buffer));
    return SUCCESS;
}

static int client_loop(struct client *client)
{
    while (1) {
        if (handle_input(client->sockfd) == ERROR) {
            return ERROR;
        }
    }
    close(client->sockfd);
    free(client->ip);
    free(client);
    return SUCCESS;
}

int run_client(struct client *client)
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
