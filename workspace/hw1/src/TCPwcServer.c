/* TCPwcServer.c - main */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int errexit(const char *format, ...);
int wordcount(int fd);
int passiveTCP(const char *service, int qlen);

#define QLEN 5
#define LINELEN 1280

/*------------------------------------------------------------------------
* main - Iterative TCP server for DAYTIME service
*------------------------------------------------------------------------
*/
int
main(int argc, char *argv[])
{
	struct sockaddr_in fsin; /* the from address of a client */
	char *service = "8000"; /* default port number */
	int msock, ssock; /* master & slave sockets */
	int alen; /* from-address length */
	switch (argc) {
		case 1:
		break;
		case 2:
		service = argv[1];
		break;
		default:
		errexit("usage: TCPwcServer [port]\n");
	}

	// get connection
	msock = passiveTCP(service, QLEN);

	while (1) {
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if (ssock < 0)
			errexit("accept failed: %s\n", strerror(errno));
		(void) wordcount(ssock);
		(void) close(ssock);
	}
}
/*------------------------------------------------------------------------
* wordcount - do TCP wordcount and send back to client
*------------------------------------------------------------------------
*/
int
wordcount(int fd)
{
	char buf[LINELEN+1];

	// get string from client
	read(fd, buf, LINELEN);

	// do wc on string
	int wc = strlen(buf);

	// printf("msg: %s\n", buf);
	// printf("wc : %d\n", wc);
	
	// send wc back to client
	(void) write(fd, (char*) &wc, sizeof(wc));

	return 0;
}