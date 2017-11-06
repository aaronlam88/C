/* UDP_iterativeServer.c - main */

#include "errexit.h"
#include "passivesock.h"
#include "tcpFileServer.h"

#define BACKLOG 10

/**
 * run_server: do server work - get file, and send file
 * Arguements:
 * sock     - socket descripter, current open socket
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 * server will not terminate if error happen, only print error
 */
void run_server (int server_sock) {
    int sock; /* client socket */
    struct sockaddr_in src_addr; /* the from address of a client */
    socklen_t socklen = sizeof(src_addr);

    char buf[BUFSIZ]; /* message buffer; use default stdio BUFSIZ */

    int run_flag = 1;
    while (run_flag) {
        // run_flag = 0; /* for debug */
        memset (buf, 0, BUFSIZ);
        memset (&src_addr, 0, sizeof(src_addr));

        sock = accept(server_sock, (struct sockaddr *)&src_addr, &socklen);

        getFilePath(sock, buf, &src_addr, &socklen);

        sendFileName(sock, buf, src_addr, socklen);

        sendFile(sock, buf, src_addr, socklen);

        close(sock);
    }
}

/*------------------------------------------------------------------------
 * main - Iterative UDP server for file transfer service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    int sock; /* server socket */
    char *service = "9000"; /* service name or port number */

    switch (argc) {
        case 1:
        break;
        case 2:
        service = argv[1];
        break;
        default:
        errexit("usage: tcpiServer [port]\n");
    }

    sock = passivesock(service, "tcp", BACKLOG);

    run_server(sock);

    close(sock);

}
