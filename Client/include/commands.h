/*
** EPITECH PROJECT, 2024
** MYTEAMS
** File description:
** commands
*/


#pragma once

#include "client.h"

void handle_help_command(client_t *client, char *command, char *response);
void handle_login_command(client_t *client, char *request, char *response);
void handle_logout_command(client_t *client, char *request, char *response);
