/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    if (error_handling(ac, av[1]) == EXIT_FAILURE)
    {
        fprintf(stderr, "Error : Incorrect argument(s).\nUSAGE : ./server [port]\n");
        return EXIT_FAILURE;
    }
    else
    {
        server(get_hostname(), atoi(av[1]));
    }

    return 0;
}