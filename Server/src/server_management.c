/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** server management
*/

#include "server.h"
#include "utils.h"

#include "logging_server.h"

#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static void save_private_discussions(server_t *server)
{
    FILE *file = fopen("datas/server_private_discussions.save", "w");

    if (!file)
        return;
    fprintf(file, "%d\n", server->private_discussions_count);
    for (int i = 0; i < server->private_discussions_count; i++) {
        fwrite(&server->private_discussions[i].user1->uuid, sizeof(uuid_t), 1,
            file);
        fwrite(&server->private_discussions[i].user2->uuid, sizeof(uuid_t), 1,
            file);
        fwrite(&server->private_discussions[i].messages_count, sizeof(int), 1,
            file);
        fwrite(server->private_discussions[i].messages,
            sizeof(private_discussion_message_t) *
            MAX_PRIVATE_DISCUSSION_MESSAGES, 1, file);
    }
    fclose(file);
}

void shutdown_server(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->clients[i].socket != 0)
            close(server->clients[i].socket);
    close(server->socket);
    save_private_discussions(server);
    save_users(server);
    free(server);
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
    char uuidStr[37] = {0};

    if (!file)
        return;
    fscanf(file, "%d\n", &server->usersCount);
    for (int i = 0; i < server->usersCount; i++) {
        fread(&server->users[i], sizeof(user_t), 1, file);
        uuid_unparse(server->users[i].uuid, uuidStr);
        server_event_user_loaded(uuidStr, server->users[i].name);
    }
    fclose(file);
}

static void load_private_discussions(server_t *server)
{
    FILE *file = fopen("datas/server_private_discussions.save", "r");
    uuid_t user_uuid;

    if (!file)
        return;
    fscanf(file, "%d\n", &server->private_discussions_count);
    for (int i = 0; i < server->private_discussions_count; i++) {
        fread(&user_uuid, sizeof(uuid_t), 1, file);
        server->private_discussions[i].user1 = search_user_by_uuid(server,
            user_uuid);
        fread(&user_uuid, sizeof(uuid_t), 1, file);
        server->private_discussions[i].user2 = search_user_by_uuid(server,
            user_uuid);
        fread(&server->private_discussions[i].messages_count, sizeof(int), 1,
            file);
        fread(server->private_discussions[i].messages,
        sizeof(private_discussion_message_t) *
        MAX_PRIVATE_DISCUSSION_MESSAGES, 1, file);
    }
    fclose(file);
}

bool init_server(server_t *server, int port)
{
    memset(server, 0, sizeof(server_t));
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
    load_private_discussions(server);
    return true;
}
