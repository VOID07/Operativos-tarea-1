
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <curl/curl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "../header/base64.h"
#include "../header/cJSON.h"

int main()
{

    // lee el archivo de configuracion

    int width, height, channels;

    unsigned char *img = stbi_load("dog.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("error al cargar la imagen \n");
        exit(1);
    }

    printf("imagen cargada,  ancho %d px, alto %d px, canales %d \n", width, height, channels);

    // pixeles

    size_t img_size = width * height * channels;

    char *base64 = malloc(sizeof(char) * Base64encode_len(img_size));
    Base64encode(base64, img, img_size);

    cJSON *json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "filename", "dog.jpg");
    cJSON_AddNumberToObject(json, "pixel", 133);
    cJSON_AddNumberToObject(json, "width", width);
    cJSON_AddNumberToObject(json, "height", height);
    cJSON_AddNumberToObject(json, "channels", channels);
    // cJSON_AddStringToObject(json, "content-base64", "10101010101010101010dwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3ur8HjVCrA0puJnPCV27rS6BPo4CUVDcIdAWs4kfxajCZH8MIvwhOKsssssssssssssssssssssssssssssssssssssssssssHVwg9nQ3u");
    cJSON_AddStringToObject(json, "content-base64", base64);

    char *jsonString = cJSON_Print(json);
    printf("%s", jsonString);

    CURL *curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if (curl)
    {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://20.39.51.23:5000/");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);
        curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, 1000000);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // int Base64encode(char * coded_dst, const char *plain_src,int len_plain_src);
    // for (unsigned char *p = img; p != img + img_size; p += channels)
    // {
    //     printf(" valor de pixel: (%d, %d, %d) \n", *p, *(p + 1), *(p + 2));
    // }

    stbi_image_free(img);
}

// -I/mingw64/include
// gcc ImageServer.c ../source/base64.c ../source/cJSON.c -lm -o ImageServer -lcurl && ./ImageServer
// sudo apt-get install libcurl4-openssl-dev