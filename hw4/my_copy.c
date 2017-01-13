
/*********************************************************************/
/*  Author: Aaron Lam
/*  SID: 92329177 Class
/*  Description: System file IO. compare fopen(), fgetc(), fputc(), fclose() 
                with open, read(), write(), close()
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "Timer.h"

static FILE *fp_in;
static FILE *fp_out;

static int fd_in;
static int fd_out;
static double wc, us, sys;

void _fopens(const char *path_in, const char *path_out)
{
    fp_in = fopen(path_in, "r");
    fp_out = fopen(path_out, "w");

    if(fp_in < 0 || fp_out < 0)
    {
        perror("Error: ");
        exit(-1);
    }
}

void _fcloses()
{
    fclose(fp_in);
    fclose(fp_out);
}

void _cpy_1(int repeat)
{
    int c; int i;

    for(i = 0; i < repeat; ++i)
    {
        while (1)
        {
            c = fgetc(fp_in);
            if(c == EOF) break;
            fputc(c, fp_out);
        }
    }
}

void method_1(const char *path_in, const char *path_out, int repeat)
{
    _fopens(path_in, path_out);

    Timer_start();
    _cpy_1(repeat);
    Timer_elapsedTime(&wc, &us, &sys);

    _fcloses();
}

void _opens(const char *path_in, const char *path_out)
{
    fd_in = open(path_in, O_RDONLY);
    fd_out = open(path_out, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    if(fd_in < 0 || fd_out < 0)
    {
        perror("Error: ");
        exit(-1);
    }
}

void _closes()
{
    close(fd_in);
    close(fd_out);
}

void _cpy_2(int repeat)
{
    char c; int i, j;

    for(i = 0; i < repeat; ++i)
    {
        while(1) 
        {
            j = read(fd_in, &c, 1);
            if(j == 0) break;
            write(fd_out, &c, 1);
        }
    }
}

void method_2(const char *path_in, const char *path_out, int repeat)
{
    _opens(path_in, path_out);

    Timer_start();
    _cpy_2(repeat);
    Timer_elapsedTime(&wc, &us, &sys);

    _closes();
}

void _cpy_3(int repeat)
{
    char c[BUFSIZ]; int i, j;

    for(i = 0; i < repeat; ++i)
    {
        while(1) 
        {
            j = read(fd_in, c, BUFSIZ);
            if(j == 0) break;
            write(fd_out, c, j);
        }
    }
}

void method_3(const char *path_in, const char *path_out, int repeat)
{
    _opens(path_in, path_out);

    Timer_start();
    _cpy_3(repeat);
    Timer_elapsedTime(&wc, &us, &sys);

    _closes();
}

void run(int method, const char *path_in, const char *path_out, int repeat)
{
    switch(method)
    {
        case 1: method_1(path_in, path_out, repeat); break;
        case 2: method_2(path_in, path_out, repeat); break;
        case 3: method_3(path_in, path_out, repeat); break;
    }
}

int main(int argc, char const *argv[])
{
    run(atoi(argv[1]), argv[2], argv[3], atoi(argv[4]));

    printf("wallclock %lf, user %lf, system time %lf\n", wc, us, sys);

    return 0;
}