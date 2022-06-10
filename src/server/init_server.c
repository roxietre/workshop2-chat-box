/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    int opt = 1;
    server_t *server = malloc(sizeof(server_t));

    server->ip_addr = ip_addr;
    server->port = port;
    // init socket
    
    if ((server->socket = socket(AF_INET, SOCK_STREAM, 0) )== 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if( setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    // init server addr
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons( PORT );
    // bind
    int bind_ret = bind(server->socket, (struct sockaddr *)&server->addr, sizeof(server->addr));
    if (bind_ret == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    // listen
    int listen_ret = listen(server->socket, MAX_CLIENTS);
    if (listen_ret == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    server->addrlen = sizeof(server->addr);
    return server;
}