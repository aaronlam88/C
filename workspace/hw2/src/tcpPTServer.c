/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: UDP file server, pre-threaded (thread pool) server   */
/*  get file name from client, use a thread pool to handle requests  */
/*  the server process is keep alive in a forever while loop         */
/*********************************************************************/

/* udpPTServer.c - main */

#include <pthread.h>

#include "errexit.h"
#include "passivesock.h"
#include "tcpFileServer.h"

int THREAD_COUNT = 5;

pthread_mutex_t mutex;

/**
 * handle_request: handle client request, call by pthread_create
 * Arguements:
 * input: socket that created in main thread, need to cast to int before use
 * Return:
 * return nothing. 
 * get file path from client, then send file name and file content back to client
 * @author: Aaron Lam
 */
void *handle_request (void *input) {
    /* server socket descriptor */
    long *sock_pt = (long*) input;
    int server_sock = *sock_pt;
    int sock; /* client socket */

    /* message buffer; use default stdio BUFSIZ */
    char buf[BUFSIZ];

    /* the from address of a client */
    struct sockaddr_in src_addr;

    socklen_t socklen = sizeof(src_addr);

    int run_flag = 1; 
    while (run_flag) {
        // run_flag = 0; /* for mem leak check */

        /* zero out variable before use */
        memset(buf, 0, BUFSIZ);
        memset(&src_addr, 0, socklen);

        pthread_mutex_lock(&mutex);
        sock = accept(server_sock, (struct sockaddr *)&src_addr, &socklen);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        getFilePath(sock, buf, &src_addr, &socklen);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        sendFileName(sock, buf, src_addr, socklen);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        sendFile(sock, buf, src_addr, socklen);
        pthread_mutex_unlock(&mutex);

    }
    pthread_exit(NULL);
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
void run_server (int sock) {

    pthread_t thread_ids[THREAD_COUNT];

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int i;
    for(i = 0; i < THREAD_COUNT; ++i) {
        pthread_create(&thread_ids[i], &attr, handle_request, (void *) &sock);
    }

    pthread_attr_destroy(&attr);
    for(i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(thread_ids[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}

/*------------------------------------------------------------------------
 * main - UDP Pre-Thread Server for file transfer service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[]) {
    /* server socket */
    int sock;
    /* default port number */
    char *service = "9000"; 

    /* get command line input */
    switch (argc) {
        /* defaut case: port 9000, thread count 5 */
        case 1: 
        break;
        case 2:
        THREAD_COUNT = atoi(argv[1]);
        break;
        case 3:
        service = argv[1];
        THREAD_COUNT = atoi(argv[2]);
        break;
        default:
        errexit("usage: tcpPTServer [port] [thread_count]\n");
    }

    /* get server socket */
    sock = passivesock(service, "tcp", 0);

    /* run server */
    run_server(sock);

}
