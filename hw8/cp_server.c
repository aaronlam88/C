#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <langinfo.h>
#include <stdint.h>
 


#define PORT 29177
#define BACKLOG 10
//server data
static struct dirent  *dp;
static struct stat     statbuf;
static FILE *fp_ls;
static int listenfd, connfd;
static struct sockaddr_in server;

void error (const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

char *_new_dir(char *new_dir, const char *cur_dir, const char *sub_dir)
{
    strcpy(new_dir, cur_dir);
    strcat(new_dir, "/");
    strcat(new_dir, sub_dir);
    return new_dir;
}

int _print_err(const char *str)
{
    fprintf(stderr, "Error(%d) opening %s\n", errno, str);
    return errno;
}


void sendfile(const char *file_name)
{
    int fd_in = open(file_name, O_RDONLY);
    char c[BUFSIZ] = {0}; 

    while(read(fd_in, c, BUFSIZ) > 0) 
    {
        write(connfd, c, BUFSIZ);
        memset(c, 0, BUFSIZ);
    }
    close(fd_in);
}

int recur_dir(const char *dir_name)
{
    DIR *dirp;
    char new_file[BUFSIZ];

    printf("%s:\n", dir_name);

    dirp  = opendir(dir_name);

    while ((dp = readdir(dirp)) != NULL) {

        strcpy(new_file, _new_dir(new_file, dir_name, dp->d_name));

        if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || stat(new_file, &statbuf) == -1) 
          continue; 
        //skip "." and ".." directories and unknow files
        write(connfd, dp->d_name, strlen(dp->d_name));
        statbuf.st_mode & S_IFREG ? sendfile(new_file) : recur_dir(new_file);
    }
    return 0;
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


void run_server()
{
  printf("waiting for client message...\n");
  connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
  char file_name[BUFSIZ] = {0};
  if(read(connfd, file_name, BUFSIZ) < 0)
    error("read()");
  recur_dir(file_name);
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