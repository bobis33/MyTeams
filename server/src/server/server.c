/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** server
*/

//SYSTEMS INCLUDES

//LOCALES INCLUDES
#include "constants.h"
#include "network.h"

int run_server(const int port)
{
    struct sockaddr_in server_addr;
    int sockfd = 0;

    if ((sockfd = build_socket()) == ERROR)
        return ERROR;

    server_addr = config_ip(port);

    if (reuse_ip(sockfd, server_addr) == ERROR
        || bind_socket(server_addr, sockfd) == ERROR)
        return ERROR;

    return SUCCESS;

}
