#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "tcp.h"
#include "leercadena.h"

void func(int sockfd,char* comando) 
{ 
    char *buff = comando + '\x0'; 
    TCP_Write_String(sockfd, buff); 
} 

int main(int argc, char* argv[]) 
{ 
    int sockfd, port; 
    char *host;
    char comando[BUFSIZ];
    char **vector;
    int i;


    if (argc != 3) {
        printf("Uso: %s <host> <puerto>\n",argv[0]);
        return 1;
    }
    host = argv[1];
    port = atoi(argv[2]);

    printf("Looking to connect at <%s,%d>\n",host,port);
    sockfd = TCP_Open(Get_IP(host),port);

    while(1){
    // function for chat 
        puts("User@host: ");
        leer_de_teclado(BUFSIZ,comando); 
        //vector = de_cadena_a_vector(comando);
        //int size=sizeof vector;
        if (strlen(comando) > 0){
            if (strcmp(comando, "exit" ) == 0){
                func(sockfd,comando);
                break;
            }
            func(sockfd,comando);
        }
    }

    // close the socket 
    close(sockfd); 
} 