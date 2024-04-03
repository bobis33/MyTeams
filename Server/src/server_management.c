/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** server management
*/

#include "server.h"

#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void save_users(server_t *server)
{
    FILE *file = fopen("datas/server_users.save", "w");

    if (!file)
        return;
    fprintf(file, "%d\n", server->usersCount);
    for (int i = 0; i < server->usersCount; i++)
        fwrite(&server->users[i], sizeof(user_t), 1, file);
    fclose(file);
}

void shutdown_server(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->clients[i].socket != 0)
            close(server->clients[i].socket);
    close(server->socket);
    save_users(server);
}

static bool bind_and_listen(server_t *server, int port)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(server->socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(server->socket);
        return false;
    }
    if (listen(server->socket, 10) == -1) {
        close(server->socket);
        return false;
    }
    return true;
}

static void load_users(server_t *server)
{
    FILE *file = fopen("datas/server_users.save", "r");

    if (!file)
        return;
    fscanf(file, "%d\n", &server->usersCount);
    for (int i = 0; i < server->usersCount; i++)
        fread(&server->users[i], sizeof(user_t), 1, file);
    fclose(file);
}

bool init_server(server_t *server, int port)
{
    memset(server->clients, 0, sizeof(server->clients));
    memset(server->users, 0, sizeof(server->users));
    server->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->socket == -1)
        return false;
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) == -1) {
        close(server->socket);
        return false;
    }
    FD_ZERO(&server->readFds);
    FD_SET(server->socket, &server->readFds);
    if (bind_and_listen(server, port) == false)
        return false;
    load_users(server);
    return true;
}
