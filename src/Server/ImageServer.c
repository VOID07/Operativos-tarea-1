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

   t_port_val = (char *)malloc(MAXCHAR * sizeof(char));

    lens = (int *)malloc(5 * sizeof(int));

    FILE *fp = fopen("config.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    else
    {
        fgets(t_port_val, MAXCHAR, fp);
    }

    *lens = getlen(t_port_val);

    port = (char *)malloc(*lens * sizeof(char));

    int i = 0;
    while (i < *lens)
    {
        port[i] = t_port_val[i];
        i++;
    }

    free(fp);
    free(lens);
    free(t_port_val);

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
