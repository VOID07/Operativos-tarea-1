#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h> 

#define STB_IMAGE_IMPLEMENTATION
#include "../header/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../header/stb_image_write.h"

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
    fprintf(stderr, "Entered parse\n");
    // fprintf(stderr, "200 OK :D%s\n", string+payload_size-10);
    cJSON *json = cJSON_Parse(string);
    fprintf(stderr, "JSON parsed\n");

    cJSON *filename = NULL;
    cJSON *pixel = NULL;
    cJSON *content_base64 = NULL;
    filename = cJSON_GetObjectItem(json, "filename");
    // cJSON_GetStringValue
    fprintf(stderr, "JSON parsed %s\n", cJSON_PrintUnformatted(filename));

    fprintf(stderr, "Got string: %s\n", filename->valuestring);
    pixel = cJSON_GetObjectItem(json, "pixel");
    content_base64 = cJSON_GetObjectItem(json, "content-base64");
    char *content = content_base64->valuestring;
    long long sizeDecoded = Base64decode_len(content);

    char *image = (char *)malloc(sizeDecoded * sizeof(char));

    int width, height, channels, pixelNumber;
    width = cJSON_GetObjectItem(json, "width")->valueint;
    height = cJSON_GetObjectItem(json, "height")->valueint;
    channels = cJSON_GetObjectItem(json, "channels")->valueint;
    pixelNumber = cJSON_GetObjectItem(json, "pixel")->valueint;

    Base64decode(image, content);
    stbi_write_jpg(filename->valuestring, width, height, channels, image, 100);
}

int writeToLog(char *str)
{

    FILE *fptr;
    time_t rawtime;
    struct tm *timeinfo;
    char *timeNow;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    timeNow = asctime(timeinfo);
    // printf("Current local time and date: %s", asctime(timeinfo));
    char log[1000];
    int strSize = strlen(timeNow);
    strcpy(log, timeNow);
    strcpy(log + strSize, "> ");
    strSize = strlen(log);
    strcpy(log + strSize, str);
    strSize = strlen(log);
    strcpy(log + strSize, "\r\n");
    fptr = fopen("/home/PabloEsquivel/tarea1/Operativos-tarea-1/src/Server/daemon/logs/texttest.txt", "a");
    fprintf(fptr, "%s", log);
    fclose(fptr);
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
