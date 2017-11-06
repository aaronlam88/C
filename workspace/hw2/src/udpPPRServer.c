/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: UDP file server, process per request                 */
/*  get file name from client, then creat a thread to handle request */
/*  the server process is keep alive in a forever while loop         */
/*********************************************************************/

/* udpTPRServer.c - main */

#include <pthread.h>
#include <sys/wait.h>

#include "errexit.h"
#include "passivesock.h"
#include "udpFileServer.h"

static int main_pid;

/* fork_child: make sure only main can fork
 * Arguments: nothing
 * Return: 
 * return child pid or exit if already in child process
 * @author: Aaron Lam
 */
int fork_child()
{
    if(getpid() == main_pid)
        return fork();
    else
        exit(0);
}

/**
 * run_server: do server work - get file, and send file
 * use getFilePath() as blocking function before creating thread
 * Arguements:
 * sock     - socket descripter, current open socket
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 * server will not terminate if error happen, only print error
 */
void run_server (int sock) {
    main_pid = getpid();

    
    /* message buffer; use default stdio BUFSIZ */
    char buf[BUFSIZ]; 

    /* the from address of a client */
    struct sockaddr_in src_addr; 
    /* zero out the src_addr so it can be filled later */
    memset (&src_addr, 0, sizeof(src_addr)); 

    socklen_t socklen = sizeof(src_addr);

    int run_flag = 1; 
    while (run_flag) {
        // run_flag = 0; /* for mem leak check */

        /* use getFilePath() as blocked read from socket */
        getFilePath(sock, buf, &src_addr, &socklen);

        int pid = fork_child();
        if(pid < 0) {
            printf("fork() error: %s", strerror(errno));
        }
        else if (pid == 0) {
            sendFileName(sock, buf, src_addr, socklen);
            sendFile(sock, buf, src_addr, socklen);
            exit(0);
        }
    }
    wait(NULL);
}

/*------------------------------------------------------------------------
 * main - UDP Thread Per Request Server for file transfer service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[]) {
    /* server socket */
    int sock;
    /* default port number */
    char *service = "9000"; 

    /* get command line input */
    switch (argc) {
        case 1:
        break;
        case 2:
        service = argv[1];
        break;
        default:
        errexit("usage: udpPPTServer [port]\n");
    }

    /* get server socket */
    sock = passivesock(service, "udp", 0);

    /* run server */
    run_server(sock);

}
