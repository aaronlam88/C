#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

static  int sockfd;
static  struct hostent *he;
static  struct sockaddr_in server_addr;


void error (const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void get_input(int argc, char const *argv[])
{
    if(argc < 4)    
        error("argv err: [host] [port] [file|dir]");

    const char *host = argv[1];
    int port = atoi(argv[2]);

    if((he=gethostbyname(host)) == NULL)    
        error("gethostbyname()");
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error("socket()");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);

    // zero the rest of the struct
    memset(&(server_addr.sin_zero), '\0', 8);

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
        error("connect()");

    if(write(sockfd, argv[3], strlen(argv[3])) < 0)
        error("write()");

    char recv[BUFSIZ];
    int fp;
    memset(recv, 0, BUFSIZ);
    while(read(sockfd, recv, BUFSIZ) > 0)
    {
        printf("%s\n", recv);
        fp = open(recv, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
        if(fp < 0)
            error("open()");
        memset(recv, 0, BUFSIZ);
        while(read(sockfd, recv, BUFSIZ) > 0)
        {
            write(fp, recv, BUFSIZ);
            memset(recv, 0, BUFSIZ);
        }
        memset(recv, 0, BUFSIZ);
        close(fp);
    }
    
    close(sockfd);
}

int main(int argc, char const *argv[])
{
    get_input(argc, argv);
    return 0;
}