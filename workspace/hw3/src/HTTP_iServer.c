/* HTTP_iServer.c - main */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <string.h>

#include "errexit.h"
#include "passivesock.h"
#include "http_helper.h"
#include "mystring.h"
#include "Timer.h"

#define BACKLOG 10

/**
 * run_server: do server work - get file, and send file
 * Arguements:
 * sock     - socket descripter, current open socket
 * Return:
 * return nothing. Report error code (errno) if sendto() fail
 * server will not terminate if error happen, only print error
 */
void run_server (int server_sock) {
    int sock; /* client socket */
    struct sockaddr_in src_addr; /* the from address of a client */
	socklen_t socklen = sizeof(src_addr);

    char buf[BUFSIZ]; /* message buf; use default stdio BUFSIZ */
    char header[BUFSIZ]; /* header that will be return to client */

	int run_flag = 1;
	while (run_flag) {
        // run_flag = 0; /* for debug */
		memset (buf, 0, BUFSIZ);
		memset (&src_addr, 0, sizeof(src_addr));

		double wc, us, sys;

		sock = accept(server_sock, (struct sockaddr *)&src_addr, &socklen);

		read(sock, buf, BUFSIZ);
		Timer_start();

		char* filepath = _GET(buf, "filepath");

		if(filepath != NULL) {
			filepath = strtrim(filepath);

			int fd = open(filepath, O_RDONLY);
			printf("=======filepath: %s\n", filepath);

			if ( fd == -1 ) {
				// file not found, return 404
				create_http_header (header, 404, NULL, 0, 0);
				write(sock, header, strlen(header));
			} else {
				// get file size
				struct stat st;
				stat(filepath, &st);
				int size = st.st_size;

				// create respond header
				create_http_header (header, 200, basename(filepath), size, 0);
				write(sock, header, strlen(header));

				// send file
				memset(buf, 0, BUFSIZ);
				int n;
				while ( (n = read(fd, buf, BUFSIZ)) > 0 ) {
					write(sock, buf, n);
					memset(buf, 0, BUFSIZ);
				}
				close(fd);
			}
		} else {
			// error, return 400
			create_http_header (header, 400, NULL, 0, 0);
			write(sock, header, strlen(header));
		}
		// printf("%s\n", header);
		close(sock);
		Timer_elapsedTime(&wc, &us, &sys);
		printf("wallclock %lf, user %lf, system time %lf\n", wc, us, sys);
	}
	close(sock);
}

/*------------------------------------------------------------------------
 * main - Iterative TCP server for file transfer service. Using HTTP protocol
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    int sock; /* server socket */
    char *service = "9000"; /* service name or port number */

	switch (argc) {
		case 1:
		break;
		case 2:
		service = argv[1];
		break;
		default:
		errexit("usage: tcpiServer [port]\n");
	}

	sock = passivesock(service, "tcp", BACKLOG);

	run_server(sock);

	close(sock);

}
