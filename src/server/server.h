/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** server
*/

#pragma once

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <netdb.h>
#include <stdio.h>

#define MAX_CLIENTS 10
#define PORT 8888

typedef struct server_s {
    struct sockaddr_in addr;
    struct timeval timeout;

    fd_set readfds;     //> contain of file descriptors ready to be read.
    fd_set writefds;    //> contain of file descriptors ready to be write.
    fd_set fds;         //> contain of all file descriptors.

    char *ip_addr;

    int *fd_array;

    int socket;
    int fdmax;
    int port;
} server_t;

int error_handling(int ac, char *port);
char *get_hostname(void);
server_t *init_server(char *ip_addr, int port);
void run_server(server_t *server);
void server(char *ip_addr, int port);
