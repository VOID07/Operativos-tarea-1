
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



int main () {


    //lee el archivo de configuracion
    




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
    

    for (unsigned char *p = img; p!= img + img_size; p+= channels) 
    {
        printf (" valor de pixel: (%d, %d, %d) \n", *p, *(p+1), *(p+2));
    }



    stbi_image_free(img);


    

}