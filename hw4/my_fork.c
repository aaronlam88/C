/*********************************************************************/
/*  Author: Aaron Lam
/*  SID: 92329177 Class ICS 53
/*  Description: Unix process creation. Use fork() to create 4 processes
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef DEBUG
    #define DEBUGBING 0
#else
    #define DEBUGBING 1
#endif

static int K = 1000; //NUMBER OF TIME TO PRINT DEFAULT TO 1000
static int main_pid;


void ChildProcess(char c)
{
    //FOR DEBUG: SHOULDN'T COUNT IN LINE COUNT!
    if(DEBUGBING) printf("pid: %d\n", getpid()); 

    for(int i = 0; i < K; ++i)
    {
        putchar(c);
        fflush(stdout);

        //FOR DEBUG: SHOULDN'T COUNT IN LINE COUNT!
        if(DEBUGBING) sleep(0.5);
    }
}

void _error()
{
    perror("fork() error");
    exit(-1);
}

//make sure only main can fork
int fork_child()
{
    if(getpid() == main_pid)
        return fork();
    else
        exit(0);
}
void _wait()
{
    if(getpid() == main_pid)
        for(int i = 0; i < 4; ++i)
            wait(NULL);
    else
        exit(0);
}

void ParentProcess ()
{
    int pid;
    for(int i = 0; i < 4; ++i)
    {
        pid = fork_child();
        if(pid < 0) _error();
        else if (pid == 0) ChildProcess('A' + i);
        //else wait(NULL);
    }
    _wait();
}

int main(int argc, char const *argv[])
{
    argc == 2 ? K = atoi(argv[1]) : K;
    main_pid = getpid();
    ParentProcess();
    getpid() == main_pid ? printf("\n") : main_pid;
    return 0;
}