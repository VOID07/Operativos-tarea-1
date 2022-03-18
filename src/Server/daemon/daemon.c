// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <errno.h>
// #include <unistd.h>
// #include <syslog.h>
// #include <string.h>

// // sudo cp /home/pablo/Documents/operativos/tarea1/imageserver.service /etc/systemd/system
// // ExecStop=/bin/bash /home/pablo/Documents/operativos/tarea1/killimageserver.sh
// // RUN apt update && apt install build-essential -y

// int main(void) {


//     pid_t pid, sid;

//     // /* Fork off the parent process */       
//     pid = fork();
//     if (pid < 0) {
//             exit(EXIT_FAILURE);
//     }
//     /* If we got a good PID, then
//         we can exit the parent process. */
//     if (pid > 0) {
//             exit(EXIT_SUCCESS);
//     }

//     /* Change the file mode mask */
//     // umask en 0 da accesso a los files del daemon
//     umask(0);

//     /* Open any logs here */
        
//     /* Create a new SID for the child process */
//     sid = setsid();
//     if (sid < 0) {
//         /* Log any failure */
//         exit(EXIT_FAILURE);
//     }


//     /* Change the current working directory */
//     if ((chdir("/")) < 0) {
//             /* Log any failure here */
//             exit(EXIT_FAILURE);
//     }


//     /* Close out the standard file descriptors */
//     //close(STDIN_FILENO);
//     //close(STDOUT_FILENO);
//     //close(STDERR_FILENO);


//     /* Daemon-specific initialization goes here */
    
//     // FILE *fptr;

    

//     // /* The Big Loop */
//     // while (1) {
//     //     /* Do some task here ... */
//     //     printf("success \n");
//     //     fptr = fopen("/home/PabloEsquivel/tarea1/Operativos-tarea-1/src/Server/daemon/logs/texttest.txt","a");
//     //     fprintf(fptr, "success \n");
//     //     fclose(fptr);
//     //     sleep(3); /* wait 3 seconds */
//     // }


    

// }