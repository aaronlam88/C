#include "udpFileServer.h"

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
 * @author: Aaron Lam
 */
void getFilePath (int sock, char *buf, struct sockaddr_in *src_addr, socklen_t *socklen) {
    /* udp recvfrom: get data from socket */
    if (recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr *) src_addr, socklen) < 0) {
        printf("recvfrom() error: %s\n", strerror(errno));
    }
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
 * @author: Aaron Lam
 */
void sendFileName (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen) {
    /* get name of file from file path */
    char *filename = basename(buf);

    /* send file name back to client */
    int count = sendto(sock, filename, strlen(filename), 0, (struct sockaddr *)&src_addr, socklen);
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
 * @author: Aaron Lam
 */
void sendFile (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen) {
    printf("open file: %s\n", buf);
    /* open file identify by file path */
    int fd = open(buf, O_RDONLY); 
    /* if open error */
    if ( fd == -1 ) { 
        sendto(sock, NULL, 0, 0, (struct sockaddr *)&src_addr, socklen);
        printf("error openning file: '%s' '%s'\n", buf, strerror(errno));
    }

    printf("start sending...\n");
    /* send file content to client */
    int n;
    while ( (n = read(fd, buf, BUFSIZ)) > 0 ) {
        sendto(sock, buf, n, 0, (struct sockaddr *)&src_addr, socklen);
    }
    close(fd);
    printf("close file\n");

    /* send NULL to client to signal EOF */
    sendto(sock, NULL, 0, 0, (struct sockaddr *)&src_addr, socklen);
    printf("done sending\n");
}
