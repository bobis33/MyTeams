/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** main
*/

//SYSTEMS INCLUDES
#include <stdio.h>
#include <string.h>

//LOCALES INCLUDES
#include "constants.h"
#include "error.h"
#include "server.h"

int main(int argc, char *argv[])
{

    int port = 0;

    return (port = check_args(argc, argv[1])) ==
    ERROR ? EPITECH_ERROR : run_server(port);
}
