/*********************************************************************/
/*Author: Aaron Lam                                                  */ 
/*Program: Linux Shell command                                       */
/*Description: A c program that can run linux shell function         */
/*Attention: This program is unsafe. Future improvement is needed    */
/*Last Update: 02/19/2016                                            */
/*********************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define SIZ 512
#define MAX_SIZ 1024

//===================================
//structure for input parsing
static char buf[BUFSIZ]; 
static int curr_index = 0;
static char cmd[SIZ] = {0};
static char arg[SIZ] = {0};
static char fin[SIZ] = {0};
static char fou[SIZ] = {0};
//===================================
//enviroment path for command call
static char pathenv[SIZ];
//===================================
//in and out file pointer
static int fd_in = -1;
static int fd_ou = -1;
//===================================
//pipe field
static int cmd_count = 0;
static int pipefds[2];
//===================================
//functions definition and hierarchy
void set_pathenv();
  void run();
    void set_cmd();
      void set_arg();
        void set_fio();
        //switch
          void set_fin();
          void set_fou();
          void set_pip();
          void set_job();
            //if not end of input and not bgj, re_run==>call run();
//helper function
void trim();
//===================================

//imported functions from other program with small modification
//the following fuctions are not my creation
void wait_for_children()
{
  int pid;
  while ( (pid = wait(0)) > 0 )
  {
    // printf("child terminated PID = %d\n", pid);
  }
}

int open_for_reading(char *input)
{
  int fd = open(input, O_RDONLY);
  if (fd == -1)
    perror("unable to open input file");
  return fd;
}

int open_for_writing(char *output)
{
  int fd = open(output, O_CREAT|O_WRONLY|O_TRUNC, 0666);
  if (fd == -1)
    perror("unable to open input file");
  return fd;
}


void create_process(int in, int out)
{
  int pid;
  switch (pid = fork())
  {
    case -1:
      perror("fork failed"); exit(-1);
    case 0:
      dup2(in, 0);
      dup2(out, 1);
      trim(arg);
      char *envp[] = {pathenv, NULL};
      char *run[] = {cmd, arg, NULL};
      strlen(arg) == 0 ? run[1] = NULL : 0;
      if (execvpe(run[0], run, envp) == -1)
        perror("exec failed");
    default:
      break;
  }
}
//===================================
void trim(char *str)
{
    int i;
    for( i = strlen(str) - 1; i > 0 && str[i] == ' '; --i)
        ;
    str[++i] = 0;
}

void clear()
{
  memset(cmd, 0, strlen(cmd));
  memset(arg, 0, strlen(arg));
  memset(fin, 0, strlen(fin));
  memset(fou, 0, strlen(fou));
}

void set_pathenv()
{
  char *path = getenv("PATH");
  sprintf(pathenv, "PATH=%s", path);
}

void skip_space()
{
  char c = buf[curr_index++];
  while(c == ' ')
    c = buf[curr_index++];
  --curr_index;
}

void store_str(char str[], char* delim)
{
  skip_space();
  char c = buf[curr_index++];
  int i = 0;
  for(; strchr(delim, c) == NULL; c = buf[curr_index++])
  {
    str[i++] = c;
  }
  --curr_index;
}

void execute_p()
{
  if(cmd_count == 0)
  {
    strlen(fin) > 0 ? fd_in = open_for_reading(fin) : (fd_in = -1);
    create_process(fd_in, pipefds[1]);
    wait_for_children();
  }
  else if(cmd_count % 2 == 1)
  {
    create_process(pipefds[1], pipefds[0]);
    wait_for_children();
  }
  else
  {
    create_process(pipefds[0], pipefds[1]);
    wait_for_children();
  }
}

void execute()
{
  strlen(fou) > 0 ? fd_ou = open_for_writing(fou) : (fd_ou = -1);
  strlen(fin) > 0 ? fd_in = open_for_reading(fin) : (fd_in = -1);
  fd_in > 0 ? create_process(fd_in, fd_ou) : create_process(pipefds[0], fd_ou);
}

void set_job()
{
  skip_space();
  char c = buf[curr_index];
  // if(c == '&')
  // {
  //   exit(0);
  // }
  // else if(c == '\n')
  // {
  //   wait_for_children();
  // }
  // else
  // {
  //   run();
  // }
  switch(c)
  {
    case  '&': execute(); exit(0);
    case '\n': execute(); wait_for_children(); break;
    default  : run();
  }


}

void set_pip()
{
  if (pipe(pipefds) == -1)
    perror("can not create pipe");
  execute_p();
  set_job();
}

void set_fin()
{
  store_str(fin, " >|&\n");
  set_fio();
}

void set_fou()
{
  store_str(fou, " <|&\n");
  set_fio();
}

void set_fio()
{
  skip_space();
  char c = buf[curr_index++];
  switch (c)
  {
    case '<': set_fin(); break;
    case '>': set_fou(); break;
    case '|': set_pip(); break;
    case '&': --curr_index; set_job(); break;
    default : execute(); wait_for_children(); break;
  }
}

void set_arg()
{
  store_str(arg, "<>|&\n");
  set_fio();
}

void set_cmd()
{
  store_str(cmd, " <>|&\n");
  set_arg();
}

void run()
{
  clear();
  set_cmd();
}

void close_fd()
{
  close(fd_in);
  close(fd_ou);
  close(pipefds[0]);
  close(pipefds[1]);
}

int main(int argc, char const *argv[])
{
  set_pathenv();
  putchar('%');
  fgets(buf, BUFSIZ, stdin);
  run();
  close_fd();
  return 0;
}