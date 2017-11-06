/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: UDP file server, thread per request                  */
/*  get file name from client, then creat a thread to handle request */
/*  the server process is keep alive in a forever while loop         */
/*********************************************************************/

/* udpTPRServer.c - main */

#include <pthread.h>

#include "errexit.h"
#include "passivesock.h"
#include "tcpFileServer.h"

/**
 * handle_request: handle client request, call by pthread_create
 * Arguements:
 * input: storage ThreadData, need to be covert to ThreadData before use
 * Return:
 * return nothing. send file name and file content back to client
 * @author: Aaron Lam
 */
void *handle_request (void *input) {
    /* client socket */
    long *sock_pt = (long*) input;
    int sock = *sock_pt;

    /* message buffer; use default stdio BUFSIZ */
    char buf[BUFSIZ]; 
    memset(buf, 0, BUFSIZ);

    struct sockaddr_in src_addr;
    
    getFilePath(sock, buf, NULL, 0);
    sendFileName(sock, buf, src_addr, 0);
    sendFile(sock, buf, src_addr, 0);

    close(sock);

    pthread_exit(NULL);
}

/**
 * run_server: do server work - get file, and send file
 * use getFilePath() as blocking function before creating thread
 * Arguements:
 * sock     - socket descripter, current open socket
 * Return:
 * return nothing. Report error message (errno) if error
 * @author: Aaron Lam
 */
void run_server (int server_sock) {
    int sock; /* client socket */
    /* thread id */
    pthread_t thread;
    /* thread attribule */
    pthread_attr_t attr;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    /* set detach state so main don't have to call pthread_join */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /* while loop to keep server alive 
     * variables needed for a thread are created in while
     * no share variables between threads except socket
     */
    int run_flag = 1; 
    while (run_flag) {
        // run_flag = 0; /* for mem leak check */


        /* the from address of a client */
        struct sockaddr_in src_addr; 
        /* zero out the src_addr so it can be filled later */
        memset (&src_addr, 0, sizeof(src_addr)); 

        socklen_t socklen = sizeof(src_addr);

        sock = accept(server_sock, (struct sockaddr *)&src_addr, &socklen);

        /* create thread to handle request */
        if (pthread_create(&thread, &attr, handle_request, (void*) &sock) < 0) {
            printf("pthread_create(): %s\n", strerror(errno));
        }
    }

    /* destroy attribute to void memory leak */
    pthread_attr_destroy(&attr);

    /* main thread exit */
    pthread_exit(NULL);
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
        errexit("usage: tcpTPRServer [port]\n");
    }

    /* get server socket */
    sock = passivesock(service, "tcp", 0);

    /* run server */
    run_server(sock);

}
