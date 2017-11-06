/* connectsock.c - connectsock */
#include "connectsock.h"

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */

/**
 * Arguments:
 * node - name of host to which connection is desired
 * service - service associated with the desired port
 * transport - name of transport protocol to use ("tcp" or "udp")
 * @author: Aaron Lam
 */
int connectsock(const char *node, const char *service, const char *transport ) {
    int sockfd; // socket descriptor
    int errcode; // error code return by getaddrinfo
    struct addrinfo hints; // address info hints
    struct addrinfo *res; // address info linked list that has the result

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; // set to use IPv4 only

    // set socket type
    if( (strcmp(transport, "udp")) == 0) {
        hints.ai_socktype = SOCK_DGRAM;
    } else {
        hints.ai_socktype = SOCK_STREAM;
    }

    // get address info; if error, print error then exit
    if ((errcode = getaddrinfo(node, service, &hints, &res)) != 0) {
        errexit("getaddrinfo(): %s\n", gai_strerror(errcode));
    }

    // loop through all the results and connect to the first valid address
    struct addrinfo *it; // res linkedlist iterator
    for(it = res; it != NULL; it = it->ai_next) {
        // try socket
        // if fail, try next address
        if ((sockfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol)) == -1) {
            continue;
        }
        // set SO_REUSEADDR
        int enable = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            printf("setsockopt(SO_REUSEADDR) failed\n");

        // try connect
        // if fail, close the current socket descriptor then try next address
        if ( (connect(sockfd, it->ai_addr, it->ai_addrlen)) == -1) {
            close(sockfd);
            continue;
        }
        break; // connected successfully
    }
    // free res, not needed anymore
    freeaddrinfo(res);

    if (it == NULL) {
        // looped off the end of the list with no connection
        errexit("connectsock fail!\n");
    }

    return sockfd;
}
