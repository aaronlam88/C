/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: UDP file server, prefork server                      */
/*  get file name from client, then creat a thread to handle request */
/*  the server process is keep alive in a forever while loop         */
/*********************************************************************/

/* udpTPRServer.c - main */

#include <pthread.h>

#include "errexit.h"
#include "passivesock.h"
#include "tcpFileServer.h"

int CHILD_COUNT = 5;

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
 * @author: Aaron Lam
 */
void run_server (int server_sock) {
    int sock; /* client socket */
    main_pid = getpid();
    int count;

    for(count = 0; count < CHILD_COUNT; ++count) {
        int pid = fork_child();
        if(pid < 0) {
            printf("fork() error: %s", strerror(errno));
        }
        else if (pid == 0) {
            /* message buffer; use default stdio BUFSIZ */
            char buf[BUFSIZ]; 

            /* the from address of a client */
            struct sockaddr_in src_addr;
            /* socket length */
            socklen_t socklen = sizeof(src_addr);

            int run_flag = 1; 
            while (run_flag) {
                // run_flag = 0; /* for mem leak check */

                /* zero out variable before use */
                memset(buf, 0, BUFSIZ);
                memset(&src_addr, 0, sizeof(src_addr)); 
                
                sock = accept(server_sock, (struct sockaddr *)&src_addr, &socklen);

                /* do server work */
                getFilePath(sock, buf, &src_addr, &socklen);
                sendFileName(sock, buf, src_addr, socklen);
                sendFile(sock, buf, src_addr, socklen);
            }
            exit(0);
        }
    }

    wait(NULL);
}

/*------------------------------------------------------------------------
 * main - UDP Prefork Server for file transfer service
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
        CHILD_COUNT = atoi(argv[1]);
        break;
        case 3:
        service = argv[1];
        CHILD_COUNT = atoi(argv[2]);
        default:
        errexit("usage: tcpPFServer [port] [child_num]\n");
    }

    /* get server socket */
    sock = passivesock(service, "tcp", 0);

    /* run server */
    run_server(sock);

}
