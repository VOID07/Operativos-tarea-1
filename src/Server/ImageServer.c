#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "header/httpd.h"
#include "header/tools.h"
#include "header/cJSON.h"

int main(int c, char **v)

{

    // variables necesarias
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // abre el archivo

    fp = fopen("config.conf", "r");

    // verifica si se pudo leer el archivo
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // lee la linea 1. la del puerto
    read = getline(&line, &len, fp);

    char port[4];
    strcpy(port, line + 5);

    printf("%s \n", port);

    // lee la linea 2. la direccion de la carpeta a utilizar para guardar
    read = getline(&line, &len, fp);
    char path[100];
    strcpy(path, line + 7);

    printf("%s \n", path);

    // cierra el archivo
    fclose(fp);

    // libera memoria
    if (line)
        free(line);

    // load_config();
    serve_forever(port);
    // exit(EXIT_SUCCESS);
    return 0;
}

void route()
{
    ROUTE_START()

    ROUTE_GET("/")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Hello! You are using %s", request_header("User-Agent"));
    }

    ROUTE_GET("/test")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("List of request headers:\r\n\r\n");

        header_t *h = request_headers();

        while (h->name)
        {
            printf("%s: %s\n", h->name, h->value);
            h++;
        }
    }

    ROUTE_POST("/")
    {

        printf("HTTP/2 200 \r\n\r\n");
        fprintf(stderr, "200 OK :D%s\n", payload);
    }

    ROUTE_POST("/test")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("List of request headers:\r\n\r\n");
        printf("Wow, seems that you POSTED %lld bytes: \n %s. \r\n", payload_size, payload);
        header_t *h = request_headers();

        while (h->name)
        {
            printf("%s: %s\n", h->name, h->value);
            h++;
        }
        fprintf(stderr, "200 OK :D%s\n", payload);
    }

    ROUTE_POST("/image")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Todo bien\r\n");
        parse_object(payload);
    }

    ROUTE_END()
}
