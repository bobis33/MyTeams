/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** utils
*/

#pragma once

#include "server.h"

#include <uuid/uuid.h>

user_t *search_user_by_name(server_t *server, char *name);
user_t *search_user_by_socket(server_t *server, int clientSocket);
user_t *search_user_by_uuid(server_t *server, uuid_t uuid);
bool check_user_connection(server_t *server, int clientSocket);
int search_user_client_socket(server_t *server, user_t *user);
