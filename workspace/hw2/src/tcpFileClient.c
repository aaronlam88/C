/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: TCP File Client, connect to TCP file server          */
/*     get file path from user, then send request to server          */
/*     get file name return from server, create file with file name  */
/*     get file content from server and write to local file          */
/*********************************************************************/


/* tcpFileClient.c - main */

#include "errexit.h"
#include "connectsock.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/**
 * sendFileRequest: get filepath from user, send filepath to server using socket
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - file path, using default BUFSIZ
 * Return:
 * return nothing. If error, print error on exit
 * @author: Aaron Lam
 */
int sendFileRequest (int sock, char *buf) {
    memset(buf, 0, BUFSIZ);
    printf("File name: ");
    fgets(buf, BUFSIZ, stdin);
    buf[strlen(buf) - 1] = '\0';

    if (sendto(sock, buf, strlen(buf), 0, NULL, 0) < 0) {
        errexit("sendto() error: %s\n", strerror(errno));
    }
    return 0;
}

/**
 * createFile: get file name from server, create a file with that name
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - storage filename recv from server, using default BUFSIZ
 * Return:
 * return nothing. If error, print error on exit
 * @author: Aaron Lam
 */
int createFile (int sock, char *buf) {
    memset(buf, 0, BUFSIZ);
    if ((recvfrom(sock, buf, BUFSIZ, 0, NULL, 0)) > 0) {
        printf("createFile: %s\n", buf);
        mode_t mode = 0666;
        int fd = open(buf, O_WRONLY | O_CREAT, mode);
        if ( fd == -1 ) {
            errexit("open() error: %s\n", strerror(errno));
        }
        return fd;
    }
    return -1;
}

/**
 * getFile: get file content from server, then write content to file in fd
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - storage filename recv from server, using default BUFSIZ
 *          - use as buf for message get from server
 * fd       - file descriptor, current open file
 * Return:
 * return nothing. If error, print error on exit
 * @author: Aaron Lam
 */
int getFile (int sock, char *buf, int fd) {
    printf("start get file ...\n");
    if (fd == -1) return -1;
    int n;
    while ( (n = recvfrom(sock, buf, BUFSIZ, 0, NULL, 0)) > 0) {
        if (write (fd, buf, n) < 0 ) {
            errexit("write() error: %s\n", strerror(errno));
        }
    }
    if (n == -1) {
        errexit("recvfrom() error: %s\n", strerror(errno));
    }
    close(fd);
    printf("done\n");
    return 0;
}

void run_client(int sock) {
    char buf[BUFSIZ];
    int fd;

    if (sendFileRequest(sock, buf) == -1) {
        errexit("sendFileRequest() error: %s\n", strerror(errno));
    }

    if ((fd = createFile(sock, buf)) == -1){
        errexit("createFile() error: %s\n", strerror(errno));
    }

    if (getFile(sock, buf, fd) == -1) {
        errexit("getFile() error: %s\n", strerror(errno));
    }
}

/*------------------------------------------------------------------------
 * main - TCP File Client for TCP File Service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[]) {
    char *host = "localhost"; /* host to use if none supplied */
    char *service = "9000"; /* default service name */

    switch (argc) {
        case 1:
        host = "localhost";
        break;
        case 3:
        service = argv[2];
        /* FALL THROUGH */
        case 2:
        host = argv[1];
        break;
        default:
        fprintf(stderr, "usage: tcpFileClient [host [port]]\n");
        return 1;
    }

    int sock = connectsock(host, service, "tcp");

    run_client(sock);

    return 0;
}
