/* UDP_iterativeServer.c - main */

#include "errexit.h"
#include "passivesock.h"
#include "udpFileServer.h"

/**
 * run_server: do server work - get file, and send file
 * Arguements:
 * sock     - socket descripter, current open socket
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 * server will not terminate if error happen, only print error
 */
void run_server (int sock) {
    char buf[BUFSIZ]; /* message buffer; use default stdio BUFSIZ */

    struct sockaddr_in src_addr; /* the from address of a client */
    memset (&src_addr, 0, sizeof(src_addr));

    socklen_t socklen = sizeof(src_addr);

    while (1) {
    	memset (buf, 0, BUFSIZ);

        getFilePath(sock, buf, &src_addr, &socklen);

        sendFileName(sock, buf, src_addr, socklen);

        sendFile(sock, buf, src_addr, socklen);
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
        errexit("usage: UDP_iterativeServer [port]\n");
    }

    sock = passivesock(service, "udp", 0);

    run_server(sock);

}
