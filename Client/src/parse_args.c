/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** main.c
*/

#include <arpa/inet.h>
#include <string.h>

#include "client.h"

int parse_args(const char *ip, const char *port, client_t *client)
{
    int inet_pton_return = 0;
    int converted_port = atoi(port);

    if (converted_port <= 0 || converted_port > 65535) {
        write(2, "Port must be between 0 and 65535\n", 34);
        return ERROR;
    }
    client->port = htons(converted_port);
    inet_pton_return =
        inet_pton(AF_INET, ip, &client->socket_address.sin_addr);
    if (inet_pton_return <= 0) {
        perror("inet_pton");
        return ERROR;
    } else {
        client->ip = strdup(ip);
        return SUCCESS;
    }
}
