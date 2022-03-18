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

int parse_object(char *value)
{
    // clean_string(value);
    fprintf(stderr, "Starting parse\n");
    // return 0;
    // fprintf(stderr, "200 OK :D%s\n", value+payload_size-10);
    cJSON *json = cJSON_Parse(value);
     if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return 0;
    }
    fprintf(stderr, "JSON parsed\n");

    cJSON *filename = NULL;
    cJSON *pixel = NULL;
    cJSON *content_base64 = NULL;
    filename = cJSON_GetObjectItem(json, "filename");
    // cJSON_GetStringValue
    // fprintf(stderr, "JSON parsed %s\n", cJSON_PrintUnformatted(filename));

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
    
    return 0;
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
    char *log = calloc(1000, sizeof(char));
    int strSize = strlen(timeNow);
    strcpy(log, timeNow);
    strcpy(log + strSize, "> ");
    strSize = strlen(log);
    memcpy(log+strSize, str, 500);
    strSize = strlen(log);
    strSize = strlen(log);
    strcpy(log + strSize, "\r\n");
    fprintf(stderr, "Writing to log\n");
    fptr = fopen("daemon/logs/log.txt", "a");
    fprintf(fptr, "%s", log);
    fclose(fptr);
}

void clean_string(char *string) // Removes whitespaces from string
{
    // char *current_pos = strchr(string,"�");
    // while (current_pos) {
    //     *current_pos = '/';
    //     current_pos = strchr(current_pos,"�");
    // }
    char buggi = *(string + 1);
    int j, n = (int)payload_size;
    for (int i = j = 0; i < n; i++)
        if (*(string + i) != buggi & *(string + i) != '\n' & *(string + i) != ' ')
            string[j++] = string[i];
    string[j] = '\0';
fprintf(stderr, "String is clean\n");
    // payload_size
}
