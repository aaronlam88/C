#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

// the port client will be connecting to
//#define PORT 7777
// max number of bytes we can get at once
#define MAXDATASIZE 300
 
int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    // connector’s address information
    struct sockaddr_in their_addr;


     
    // if no command line argument supplied
    if(argc != 4)
    {
        fprintf(stderr, "argv err: username host port", argv[0]);
        // just exit
        exit(1);
    }

    char *username = argv[1];
    char *host = argv[2];
    int PORT = atoi(argv[3]);
     
    // get the host info
    if((he=gethostbyname(host)) == NULL)
    {
        perror("gethostbyname()");
        exit(1);
    }
     
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket()");
        exit(1);
    }
    
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);

    // zero the rest of the struct
    memset(&(their_addr.sin_zero), '\0', 8);
     
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }

    fgets(buf, MAXDATASIZE, stdin);

    if(write(sockfd, buf, MAXDATASIZE) < 0)
    {
        perror("send()");
        exit(1);
    }
     
    if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
        perror("recv()");
        exit(1);
    }

    printf("Client-Received: %s", buf);     
    printf("Client-Closing sockfd\n");

    close(sockfd);

    return 0;
}