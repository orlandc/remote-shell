#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include "leercadena.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 1024

// Function designed for chat between client and server. 
char *func(int sockfd) { 
    char buff[MAX];  
    bzero(buff,MAX);
    char * response;
    
    response = malloc(sizeof(char)*MAX);

    TCP_Read_String(sockfd, buff, MAX); 
    //printf("Se leyo %s\n",buff);

    strcat(response, buff);

    return response;
} 

void sendFile(int  connfd){
    char *filename= "./1.txt";
    TCP_Send_File(connfd,filename);
}

void command_shell(char * buffed) {
    char buffy[MAX];
    bzero(buffy,MAX);
    char **vector;
    int child_pid;
    FILE *stream;

    vector = de_cadena_a_vector(buffed);
    child_pid = fork();
    
    if(child_pid == 0) {
        printf("\n");
        if((stream = freopen("1.txt", "w", stdout)) == NULL){
            exit(1);
        }
        execvp(vector[0],vector);
        printf("\n");
        vector = NULL;
  		printf("Error in excuting the command- please make sure you type the right syntax.\n");
        exit(1);
    }
}


// Driver function 
int main(int argc, char *argv[]) {
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
        char * resultado = func(connfd);
        // printf("Se leyo %s\n", *resultado);
        if (*resultado == 101 || *resultado == 0){
            printf("Fin de la conexion \n");
            break;
        } else {
            command_shell(resultado);
            sendFile(connfd);
        }
    }

    close(socket); 
} 