/**
 * @author: Aaron Lam
 */
#ifndef CONNECTSOCK_H_
#define CONNECTSOCK_H_

#include "errexit.h"

#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif /* INADDR_NONE */

typedef unsigned short u_short;

int connectsock (const char *host, const char *service, const char *transport);

#endif
