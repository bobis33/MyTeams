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
    my_put_str("USAGE: ./myteams_server port\n\n       "
    "port  is the port number on which the server socket listens\n");
    return return_code;
}

int check_args(const int argc, const char* port)
{

    int port_to_int = 0;

    if (argc != 2)
        return print_help(ERROR);

    if (argc == 2) {
        if (strcmp(port, "-help") == 0)
            return print_help(SUCCESS);

        return (port_to_int = is_port(port)) == ERROR ? ERROR : port_to_int;
    }

    return print_help(ERROR);

}
