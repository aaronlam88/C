/* UDPdaytime.c - UDPdaytime, main */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#define LINELEN 128
#define MSG "what time is it?\n"

int UDPdaytime(const char *host, const char *service);
int connectUDP(const char *host, const char *service);
int errexit(const char *format, ...);

/*------------------------------------------------------------------------
* main - UDP client for DAYTIME service
*------------------------------------------------------------------------
*/
int
main(int argc, char *argv[])
{
	char *host = "localhost"; /* host to use if none supplied */
	char *service = "13"; /* default service name */
	
	switch (argc) {
		case 1:
		host = "localhost";
		break;
		case 3:
		service = argv[2];
		/* FALL THROUGH */
		case 2:
		host = argv[1];
		break;
		default:
		fprintf(stderr, "usage: UDPdaytime [host [port]]\n");
		exit(1);
	}
	UDPdaytime(host, service);
	exit(0);
}

/*------------------------------------------------------------------------
* UDPdaytime - invoke DAYTIME on specified host and print results
*------------------------------------------------------------------------
*/
int
UDPdaytime(const char *host, const char *service)
{
	char buf[LINELEN+1]; /* buffer for one line of text */
	int s, n; /* socket, read count */

	s = connectUDP(host, service);

	(void) write(s, MSG, strlen(MSG));

	n = read(s, buf, LINELEN);
	buf[n] = '\0'; /* ensure null-terminated */
	(void) fputs( buf, stdout );

	return 0;
}