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
void handle_users_command(client_t *client, char *request, char *response);
void handle_user_command(client_t *client, char *request, char *response);
void handle_send_command(client_t *client, char *request, char *response);
void handle_messages_command(client_t *client, char *request, char *response);
void handle_create_command(client_t *client, char *request, char *response);
void handle_use_command(client_t *client, char *request, char *response);
void handle_subscribe_command(client_t *client, char *request, char *response);
void handle_unsubscribe_command
(client_t *client, char *request, char *response);
void handle_subscribed_command
(client_t *client, char *request, char *response);
