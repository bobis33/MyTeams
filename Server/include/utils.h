/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** utils
*/

#pragma once

#include "server.h"

#include <uuid/uuid.h>

char *clear_command(char *command);
user_t *search_user_by_name(server_t *server, char *name);
