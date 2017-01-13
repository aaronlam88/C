#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("start\n");

    int i = 0;
    for(i = 0; i < 3; ++i)
    {
        int pid = fork();
        if(pid == 0)
            printf("child\n");
        else
            wait(NULL);
    }

    return 0;
}