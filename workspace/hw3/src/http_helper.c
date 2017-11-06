/* HTTP_header.c */
#include "http_helper.h"
/**
 * @author: Aaron Lam
 */

/**
 * create_http_header: create a http header following http protocol
 * @author: Aaron Lam
 */

void create_http_header (char* header, int status_code, char* filename, int length, int keep_alive) {
	keep_alive = 0; // disable keep_alive for current version

	memset(header, 0, BUFSIZ);

	// set status code
	switch(status_code) {
		case 200: strcpy(header, "HTTP/1.1 200 OK\r\n"); break;
		case 400: strcpy(header, "HTTP/1.1 400 Bad Request\r\n"); break;
		case 404: strcpy(header, "HTTP/1.1 404 Not Found\r\n"); break;
		default: printf("status_code not supported\n"); strcpy(header, "HTTP/1.1 404 Not Found\r\n"); break;
	}

	// set date
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char* datetime = asctime (timeinfo);
	datetime[strlen(datetime)-1] = ' ';
	strcat(header, "Date: ");
	strcat(header, datetime);
	strcat(header, "GMT\r\n");

	// set server
	strcat(header, "Server: AaronLam HTTP Server\r\n");

	// set content-ranges
	strcat(header, "Content-Range: bytes\r\n");

	if(length > 0) {

		char str[15];
		sprintf(str, "%d\r\n", length);
		strcat(header, "Content-Length: ");
		strcat(header, str);
	}
	if(filename != NULL) {
		strcat(header, "Content-Disposition: attachment; filename=");
		strcat(header, filename);
		strcat(header, "\r\n");
	}

	strcat(header, "Connection: close\r\n");

	strcat(header, "\r\n");
}

char* _GET(char* header, char* get) {
	char* token = strtok(header, "\n");
	while(token != NULL) {
		if(strstr(token, get) != NULL) {
			if(strstr(token, ":")) {
				token = strtok(token, ":");
				token = strtok(NULL, " \n");
			}
			if(strstr(token, "=")) {
				token = strtok(token, "=");
				token = strtok(NULL, " ");
			}
			break;
		}
		token = strtok(NULL, "\n");
	}
	return token;
}