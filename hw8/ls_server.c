#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 29177
#define BACKLOG 10

static FILE *fp_ls;
static int listenfd, connfd;
static char buffer[BUFSIZ];
static struct sockaddr_in server, client;

void error (const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void create_socket ()
{
	printf("create_socket...\n");
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error("socket() error!");
	}
}

void setup_socket()
{
	printf("setup_socket...\n");
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
}

void setup_bind()
{
	printf("bind_socket...\n");
	if(bind(listenfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		error("bind() error!");
	}
}

void setup_listen()
{
	printf("listen...\n");
	if(listen(listenfd, BACKLOG) < 0)
	{
		error("listen() error!");
	}
}

void ls_to_file(char const *cmd)
{
	fp_ls = popen(cmd, "r");
	if(fp_ls == NULL)
	{
		error("ls error!");
	}
}

void respond()
{
	printf("responding to client...\n");
	while(fgets(buffer, BUFSIZ, fp_ls) != NULL)
	{
		write(connfd, buffer, BUFSIZ);
	}
	pclose(fp_ls);
}

void do_ls()
{
	char ls[BUFSIZ] = "ls ";
	strcat(ls, buffer);
	ls_to_file(ls);
}

void run_server()
{
	printf("waiting for client message...\n");
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
	recv(connfd, buffer, BUFSIZ, 0);
	do_ls();
	respond();
	close(connfd);
	printf("respond sent!\n");
}

int main(int argc, char const *argv[])
{
	create_socket();
	setup_socket();
	setup_bind();
	setup_listen();
	run_server();

	return 0;
}