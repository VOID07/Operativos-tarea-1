#include <stdio.h>
#include <time.h>
#include <stdlib.h>



int main()
{
    FILE *fptr;
    
    fptr = fopen("/home/pablo/Documents/operativos/tarea1/log.txt","a");
    fprintf(fptr, "========================================== \n\n");
    fprintf(fptr, "ImageServer iniciado  \n\n");


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    fprintf(fptr, "fecha:  ");
    fprintf(fptr, "%d-%02d-%02d %02d:%02d:%02d\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    fprintf(fptr, "========================================== \n");
    fclose(fptr);
    
    
    exit(0);



}
