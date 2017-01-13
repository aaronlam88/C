//=====================================================================
//  Author: Aaron Lam
//  SID: 92329177 Class ICS 53
//  Description: Unix command in C. Get cmd from stdin, execute the cmd.
//=====================================================================

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024

static char *cmp;
static char *arg[MAX_BUFFER_SIZE];
static char pathenv[MAX_BUFFER_SIZE];

void process_input()
{
    int i = 0;
    char buf [MAX_BUFFER_SIZE];

    fgets(buf, MAX_BUFFER_SIZE, stdin);
    char *temp = strtok(buf, " \n");
    cmp = temp;
    for(arg[i] = strtok(NULL, " \n"); arg[i] != NULL;arg[++i] = strtok(NULL, " \n"))
        ;
}

void get_pathenv()
{
    char *path = getenv("PATH");
    sprintf(pathenv, "PATH=%s", path);
}

void _run(char *arg)
{
    char * envp[] = {pathenv, NULL};
    char *run[] = {cmp, arg, NULL};
    execvpe(run[0], run, envp);
}

void run_cmd()
{
    for(int i = 0; arg[i] != NULL; ++i)
    {
        int pid = fork();
        if(pid == 0)
            _run(arg[i]);
        else
            wait(NULL);
    }
}

int main(int argc, char const *argv[])
{
    process_input();
    get_pathenv();
    run_cmd();
    return 0;
}