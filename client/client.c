#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "tcp.h"
#include "leercadena.h"

void func(int sockfd,char* comando) 
{ 
    char *buff = comando + '\x0'; 
    TCP_Write_String(sockfd, buff); 
} 
void requestFile(int sockfd){
    while(1){
        FILE *fptr; 
        char *filename = (char*)calloc(BUFSIZ,sizeof(char));
	    assert(filename != NULL);
	    TCP_Read_String(sockfd,filename,BUFSIZ); Send_ACK(sockfd);
	    //printf("Archivo a recibir [%s]\n",filename);
	    free(filename);
	    filename = "1.txt";
	    TCP_Recv_File(sockfd, filename);
        if( access( filename, F_OK ) == 0 ) {
            // Open file 
            fptr = fopen(filename, "r"); 
            if (fptr == NULL) { 
                printf("Cannot open file \n"); 
                exit(1); 
            } 
  
            // Read contents from file 
            char c = fgetc(fptr); 
            while (c != EOF) { 
                printf ("%c", c); 
                c = fgetc(fptr); 
            } 
  
            fclose(fptr);
            break;
        }
    }
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
            requestFile(sockfd);
        }
    }

    // close the socket 
    close(sockfd); 
} 