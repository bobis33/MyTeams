/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** commands
*/

#pragma once

#include "server.h"

// Misc commands
void handle_unimplemented_command(
    server_t *server, int clientSocket, char *command);
void handle_stop_server_command(server_t *server, int clientSocket,
    char *command);

// Log commands
void handle_login_command(server_t *server, int clientSocket, char *command);
void handle_logout_command(server_t *server, int clientSocket, char *command);