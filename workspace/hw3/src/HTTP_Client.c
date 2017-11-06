/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: TCP File Client, connect to TCP file server          */
/*     using HTTP protocol, send GET request and get back a file     */
/*     file will be save to current director /download folder        */
/*********************************************************************/


/* HTTP_Client.c - main */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <sys/wait.h>

#include "errexit.h"
#include "connectsock.h"

void run_client(int sock) {
	char buf[BUFSIZ];
	char filepath[BUFSIZ];
	char filename[BUFSIZ];

	struct stat st;
	memset(&st, 0, sizeof(st));

	if (stat("./download", &st) == -1) {
		mkdir("./download", 0700);
	}

	memset(buf, 0, BUFSIZ);
	memset(filepath, 0, BUFSIZ);
	memset(filename, 0, BUFSIZ);

	printf("GET (full path): ");

	scanf("%s", filepath);

	strcat(filename, "./download/");
	strcat(filename, basename(filepath));

	strcat(buf, "filepath:");
	strcat(buf, filepath);

	write(sock, buf, sizeof(buf));

	int fd;
	int count;
	int header = 0;
	memset(buf, 0, BUFSIZ);
	while((count = read(sock, buf, BUFSIZ)) > 0) {
		if(header == 0) {
			header = 1;
			char* httpbody = strstr(buf, "\r\n\r\n");
			if(httpbody) {
				httpbody += 4;
			}
			count = count - (httpbody - buf);
			if (count == 0) {
				printf("ERROR\n%s\n", buf);
				break;
			}

			printf("createFile: %s\n", filename);
			mode_t mode = 0666;
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
			if ( fd == -1 ) {
				errexit("open() error: %s\n", strerror(errno));
			}
			write(fd, httpbody, count);
		}else {
			write(fd, buf, count);
		}
		memset(buf, 0, BUFSIZ);
	}
	close(fd);

	close(sock);

	printf("done\n");
}

/*------------------------------------------------------------------------
 * main - TCP File Client for TCP File Service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[]) {
    char *host = "localhost"; /* host to use if none supplied */
    char *service = "9000"; /* default service name */

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
		fprintf(stderr, "usage: HTTP_Client [host [port]]\n");
		return 1;
	}

	int sock = connectsock(host, service, "tcp");

	run_client(sock);

	return 0;
}
