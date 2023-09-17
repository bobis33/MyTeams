/*
** EPITECH PROJECT, 2023
** MyTeams-alpha-
** File description:
** ip
*/

// SYSTEMS INCLUDES
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

//LOCALES INCLUDES
#include "constants.h"

static const int reuse_error(void)
{
    perror("option reuse failed");
    return ERROR;
}

int reuse_ip(const int sockfd, struct sockaddr_in server_addr)
{

    return setsockopt(sockfd,
                        SOL_SOCKET,
                        SO_REUSEADDR,
                        &server_addr,
                        sizeof(server_addr)) == -1 ? reuse_error()
                                                    : SUCCESS;
}

struct sockaddr_in config_ip(const int port)
{

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    return server_addr;
}
