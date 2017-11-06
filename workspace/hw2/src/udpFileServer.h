#ifndef UDP_FILE_SERVER_H
#define UDP_FILE_SERVER_H

#include "errexit.h"
#include "passivesock.h"

#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <string.h>
#include <sys/wait.h>

void getFilePath (int sock, char *buf, struct sockaddr_in *src_addr, socklen_t *socklen);

void sendFileName (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen);

void sendFile (int sock, char *buf, struct sockaddr_in src_addr, socklen_t socklen);

#endif
