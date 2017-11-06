#ifndef PASSIVESOCK_H
#define PASSIVESOCK_H

#include "errexit.h"

#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>


int passivesock(const char *service, const char *transport, int qlen);

#endif
