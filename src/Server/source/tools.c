#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../header/tools.h"
#include "../header/cJSON.h"
#include "../header/httpd.h"
#include "../header/base64.h"

int getlen(char line[])
{
    int len = 0;
    while (line[len] != '\n')
    {
        len++;
    }
    return len;
}

void parse_object(char *string)
{
    clean_string(string);    
    cJSON *json = cJSON_Parse(string);

    cJSON *filename = NULL;
    cJSON *pixel = NULL;
    cJSON *content_base64 = NULL;

    filename = cJSON_GetObjectItem(json, "filename");
    pixel = cJSON_GetObjectItem(json, "pixel");
    content_base64 = cJSON_GetObjectItem(json, "content-base64");
    char *content = content_base64->valuestring;
    long long sizeDecoded = Base64decode_len(content);
    char *image = (char*) malloc(sizeDecoded*sizeof(content[0]));

    Base64decode(image, content);
    printf("Decoded content: %s\r\n", image);
    // char *systemCall = (char*)malloc((strlen(image->valuestring) + 100) * sizeof(char));
    // int res = 0;

    // if (operation->valueint)
    // {
    //     strcpy(systemCall, "/usr/bin/python3 ");
    //     strcat(systemCall, pyS_path);
    //     strcat(systemCall, "histograma.py ");
    //     strcat(systemCall, histo_path);
    //     strcat(systemCall, " ");
    //     strcat(systemCall, image->valuestring);
    //     res = system(systemCall);
    // }
    // else
    // {
    //     strcpy(systemCall, "/usr/bin/python3 ");
    //     strcat(systemCall, pyS_path);
    //     strcat(systemCall, "colors.py ");
    //     strcat(systemCall, colores_path);
    //     strcat(systemCall, " ");
    //     strcat(systemCall, image->valuestring);
    //     res = system(systemCall);
    // }
    // free(systemCall);
}

void clean_string(char *string) // Removes whitespaces from string
{
    char buggi = *(string + 1);
    int j, n = (int)payload_size;
    for (int i = j = 0; i < n; i++)
        if (*(string + i) != buggi & *(string + i) != '\n' & *(string + i) != ' ')
            string[j++] = string[i];
    string[j] = '\0';

    // payload_size
}
