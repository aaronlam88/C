/* TCPdaytime.c - TCPdaytime, main */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <time.h>

#define UNIXEPOCH 2208988800 /* UNIX epoch, in UCT secs */

int TCPtime(const char *host, const char *service);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

/*------------------------------------------------------------------------
* main - TCP client for TIME service
*------------------------------------------------------------------------
*/
int
main(int argc, char *argv[])
{
    char host1[256];
    char port1[6];
    char host2[256];
    char port2[6];

    printf("Please enter host1 address: ");
    scanf("%s", host1);
    printf("port1: ");
    scanf("%s", port1);

    printf("Please enter host2 address: ");
    scanf("%s", host2);
    printf("port2: ");
    scanf("%s", port2);

    int time1 = TCPtime(host1, port1);
    int time2 = TCPtime(host2, port2);

    printf("Time diff: %d\n", time2 - time1);
    exit(0);
}

/*------------------------------------------------------------------------
* TCPtime - invoke TIME on specified host and print results
*------------------------------------------------------------------------
*/
int
TCPtime(const char *host, const char *service)
{
    int s, n; /* socket, read count */
    time_t now; /* 32-bit integer to hold time */

    s = connectTCP(host, service);

    /* Read the time */
    n = read(s, (char *)&now, sizeof(now));
    if (n < 0)
        errexit("read failed: %s\n", strerror(errno));
    now = ntohl((u_long)now); /* put in host byte order */
    now -= UNIXEPOCH; /* convert UCT to UNIX epoch */

    //print result
    printf("%s: %s", host, ctime(&now));

    return (int) now;
}