/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include <errno.h>
#include "server.h"

void run_server(server_t *serv)
{
    int max_sd;
    int new_socket;
    int max_clients = MAX_CLIENTS;
    int sd;
    int activity;
    int valread;
    char buffer[1025];
    char *message = "ta maman est plus que c'elle que c'elle de tristan";
    while (1)
    {
        FD_ZERO(&serv->readfds);
        FD_ZERO(&serv->writefds);
        FD_SET(serv->socket, &serv->fds);
        max_sd = serv->socket;
        for (int i = 0 ; i < max_clients ; i++)
        {
            sd = serv->client_socket[i];
            if(sd > 0)
                FD_SET( sd , &serv->readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        printf("Waiting for activity...\n");
        activity = select( max_sd + 1 , &serv->readfds , &serv->writefds , NULL , NULL);
        if ((activity < 0))
        {
            printf("select error");
        }
        printf("Activity\n");
        printf("accepting new connection\n");
        if (FD_ISSET(serv->socket, &serv->readfds))
        {
            if ((new_socket = accept(serv->socket,
                    (struct sockaddr *)&serv->ip_addr, (socklen_t*)&serv->addr)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
        }
        printf("new connection\n");
        if( send(new_socket, message, strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }
            puts("Welcome message sent successfully");
            for (int i = 0; i < max_clients; i++)
            {
                if( serv->client_socket[i] == 0 )
                {
                    serv->client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        for (int i = 0; i < max_clients; i++)
        {
            sd = serv->client_socket[i];
            if (FD_ISSET( sd , &serv->readfds))
            {
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    getpeername(sd , (struct sockaddr*)&serv->addr , \
                        (socklen_t*)&serv->addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                          inet_ntoa(serv->addr.sin_addr) , ntohs(serv->addr.sin_port));
                    close( sd );
                    serv->client_socket[i] = 0;
                }
                else
                {
                    buffer[valread] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
    return;
}
