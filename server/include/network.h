/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** network
*/

// SYSTEMS INCLUDES
#include <netinet/in.h>

#ifndef NETWORK_H_
    #define NETWORK_H_
    int is_port(const char *port);
    struct sockaddr_in config_ip(const int port);
    int build_socket(void);
    int bind_socket(struct sockaddr_in server_addr, const int sockfd);
    int reuse_ip(const int sockfd, struct sockaddr_in server_addr);

#endif /* !NETWORK_H_ */
