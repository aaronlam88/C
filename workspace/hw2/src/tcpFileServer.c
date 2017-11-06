#include "tcpFileServer.h"

/**
 * @author: Aaron Lam
 */

/**
 * getFilePath: get file path from client connected to current socket.
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - buffer to storage message, using default BUFSIZ
 * src_addr - source address, will be filled by this function
 *          - src_addr need to be saved for later use
 * socklen  - socket length, size of src_addr
 * Return:
 * the requested file path from client is save buf for later use
 * return nothing. Report error code (errno) if recvfrom() fail
 */
void getFilePath (int sock, char *buf, struct sockaddr_in *src_addr, socklen_t *socklen) {
    int n = recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr *) src_addr, socklen);
    if (n < 0) {
        printf("recvfrom() error: %s\n", strerror(errno));
    }
    buf[n] = '\0';
    return;
}

/**
 * sendFileName: send file name back to client, act as connection check.
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - buffer to storage message, using default BUFSIZ
 * src_addr - server source address, pass in as value
 * socklen  - socket length, size of src_addr
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 */
void sendFileName (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen) {
    char filename[BUFSIZ];
    memset(filename, 0, BUFSIZ);
    strcpy(filename, basename(buf));
    filename[strlen(filename)] = '\0';

    int count = sendto(sock, filename, strlen(filename)+1, 0, (struct sockaddr *)&src_addr, socklen);
    if (count < 0) {
        printf("sendto() error: %s\n", strerror(errno));
    }
}

/**
 * sendFile: open the requested file, then send file back to client.
 * Arguements:
 * sock     - socket descripter, current open socket
 * buf      - buffer to storage message, using default BUFSIZ
 * src_addr - server source address, pass in as value
 * socklen  - socket length, size of src_addr
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 */
void sendFile (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen) {
    printf("open file: %s\n", buf);
    int fd = open(buf, O_RDONLY); //open file identify by file path
    if ( fd == -1 ) { 
        sendto(sock, NULL, 0, 0, (struct sockaddr *)&src_addr, socklen);
        printf("error openning file: '%s' '%s'\n", buf, strerror(errno));
    }

    printf("start sending...\n");
    int n;
    while ( (n = read(fd, buf, BUFSIZ)) > 0 ) {
        sendto(sock, buf, n, 0, (struct sockaddr *)&src_addr, socklen);
    }
    close(fd);
    printf("close file\n");

    close(sock);
    printf("done sending\n");
}
