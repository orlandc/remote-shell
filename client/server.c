#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include "leercadena.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 80

// Function designed for chat between client and server. 
char func(int sockfd) 
{ 
    char buff[MAX]; 
    char **vector;
    int red=fork();
    bzero(buff,MAX);
    TCP_Read_String(sockfd, buff, MAX); 
    printf("Se leyo %s\n",buff);
    vector = de_cadena_a_vector(buff);
    if(red == 0){
        int old_stdout = dup(1);
        FILE *fp1= freopen("file.txt","a+",stdout);
        if(execvp(vector[0],vector)<0)//{
            printf("EXEC Failed\n");
        fclose(stdout);
        FILE *fp2 = fdopen(old_stdout, "w");
        *stdout = *fp2;
        exit(1);

    //  execvp(vector[0],vector);
    //  execvp(buff,a);
    //  perror ("failed execute command");  
    }
    return *buff;
} 


// Driver function 
int main(int argc, char *argv[]) 
{ 
    int socket, connfd;  
    int puerto;

    if (argc != 2) {
        printf("Uso: %s <puerto>\n",argv[0]);
        return 1;
    }
    
    puerto = atoi(argv[1]);

    socket = TCP_Server_Open(puerto);
    connfd = TCP_Accept(socket);
    while(1){
        char resultado= func(connfd);
        if (resultado == 101 || resultado == 0){
            printf("Fin de la conexion \n");
            break;
        }
    }
    // After chatting close the socket 
    close(socket); 
} 