//  Server.h
//
//  Created by  Dagoberto Rojas on  3/3/2022 following https://www.youtube.com/watch?v=gk6NL1pZi1M
//
#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(void);
};

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*lauch)(void));


#endif /* Server_h */