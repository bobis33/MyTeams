/*
** EPITECH PROJECT, 2023
** MyTeams-alpha-
** File description:
** socket
*/

// SYSTEMS INCLUDES
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

//LOCALES INCLUDES
#include "constants.h"

static const int socket_error(void)
{
    perror("Erreur lors de la création du socket");
    return ERROR;
}

int build_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    return sockfd == -1 ? socket_error() : sockfd;

}

static const int bind_socket_error(const int sockfd)
{
    perror("Erreur lors de l'attachement du socket");
    close(sockfd);
    return ERROR;
}

int bind_socket(struct sockaddr_in server_addr, const int sockfd)
{
    int bind_value = 0;

    return (bind_value = bind(sockfd,
                        (struct sockaddr*)&server_addr,
                        sizeof(server_addr))) == -1 ? bind_socket_error(sockfd)
                                                    : bind_value;
}
