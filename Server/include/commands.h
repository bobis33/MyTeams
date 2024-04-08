/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** commands
*/

#pragma once

#include "server.h"

// Misc commands
void handle_unimplemented_command(server_t *server, int clientSocket,
    char *command);
void handle_stop_server_command(server_t *server, int clientSocket,
    char *command);
void handle_help_command(server_t *server, int clientSocket, char *command);

// Log commands
void handle_login_command(server_t *server, int clientSocket, char *command);
void handle_logout_command(server_t *server, int clientSocket, char *command);

// User commands
void handle_users_command(server_t *server, int clientSocket, char *command);
void handle_user_command(server_t *server, int clientSocket, char *command);

// Private discussion commands
void handle_send_command(server_t *server, int clientSocket, char *command);
void handle_messages_command(server_t *server, int clientSocket,
    char *command);

// Team commands
void handle_create_command(server_t *server, int clientSocket, char *command);
void handle_use_command(server_t *server, int clientSocket, char *command);
