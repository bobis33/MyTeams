/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** error
*/

//SYSTEMS INCLUDES
#include <string.h>

//LOCALES INCLUDES
#include "constants.h"
#include "utils.h"
#include "network.h"

static int print_help(const int return_code)
{

    my_put_str("USAGE: ./myteams_cli ip port\n\n       "
    "ip    is the server ip adress on which the server socker listens\n       "
    "port  is the port number on which the server socket listens\n");

    return return_code;
}

int check_args(const int argc, const char *ip, const char *port)
{

    int port_to_int = 0;

    if (argc != 2 && argc != 3)
        return print_help(ERROR);

    if (argc == 2 && strcmp(ip, "-help") == 0)
        return print_help(SUCCESS);

    if (argc == 3) {
        return is_ip(ip) == ERROR
            || (port_to_int = is_port(port)) == ERROR ? ERROR : port_to_int;
    }

    return print_help(ERROR);

}
