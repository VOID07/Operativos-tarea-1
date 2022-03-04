//  test.c
//
//  Created by  Dagoberto Rojas on  3/3/2022 following https://www.youtube.com/watch?v=gk6NL1pZi1M
//
#include "Server.h"
#include <stdio.h>

void launch(struct Server *server){
    printf("=======WAITING FOR CONNECTION=======");
    int new_socket = accept(server->socket,);
}


int main(){
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10);
    return 0;
}