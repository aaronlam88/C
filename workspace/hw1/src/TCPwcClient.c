/* TCPwcClient.c - main */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <time.h>

#define LINELEN 128

int TCPgetwc(const char *host, const char *service, char* str);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

/*------------------------------------------------------------------------
* main - TCP client for DAYTIME service
*------------------------------------------------------------------------
*/
int
main(int argc, char *argv[])
{
    char *host = "localhost"; /* host to use if none supplied */
    char *service = "8000"; /* default port number */

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
		fprintf(stderr, "usage: TCPwcClient [host [port]]\n");
		exit(1);
	}

	char str[LINELEN+1];

	// get user input
	printf("Please enter your string: ");
	fgets (str, LINELEN, stdin);

	// do wc and get server wc
	TCPgetwc(host, service, str);
	exit(0);
}

/*------------------------------------------------------------------------
* TCPgetwc - do wc on msg and compare the wc with server
*------------------------------------------------------------------------
*/
int
TCPgetwc(const char *host, const char *service, char* str)
{
    int l_count = strlen(str);

    int s = connectTCP(host, service);

    (void) write(s, str, LINELEN);

	int s_count;
	read(s, (char*) &s_count, sizeof(s_count));


	printf("Your string: %s", str);
	printf("Local count: %d\n", l_count);
	printf("Server count: %d\n", s_count);

	return 0;
}