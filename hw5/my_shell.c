/*********************************************************************/
/*  Author: Aaron Lam                                                */
/*  SID: 92329177 Class ICS 53                                       */
/*  Description: A C program that mimic Linux bash shell             */
/*              This is a very simple shell that can only handle one */
/*              line command, and no piping                          */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARG_LIST_SIZE 1024

typedef struct
{
    char cmd[BUFSIZ];
    char arg_list[BUFSIZ];
    char io_in[BUFSIZ];
    char io_out[BUFSIZ];
}LINE;

static LINE line;

static char buf[BUFSIZ];
static int curr_index = 0;

void set_io_redirect();

void skip_space()
{
    while(buf[curr_index] == ' ' && buf[curr_index] != '\n')
        ++curr_index;
}

void set_cmd()
{
    char *temp = strtok(buf, " \n");
    strcpy(line.cmd, temp);
}


void set_arg_list()
{
    char *temp = strtok(NULL, "<>\n");
    strcpy(line.arg_list, temp);
}

void set_in_file()
{
    int i = 0;
    ++curr_index;
    skip_space();

    while(buf[curr_index] != '\n' &&
        buf[curr_index] != '>')
    {
        line.io_in[i++] = buf[curr_index++];
    }
    printf("in: %s\n", line.io_in);
    set_io_redirect();
}

void set_out_file()
{
    int i = 0;
    ++curr_index;
    skip_space();
    while(buf[curr_index] != ' ' && buf[curr_index] != '\n' &&
        buf[curr_index] != '>')
    {
        line.io_out[i++] = buf[curr_index++];
    }
    printf("out: %s\n", line.io_out);
    set_io_redirect();
}

void set_io_redirect()
{
    char *temp = strtok(NULL, "\n");
    printf("%s\n", temp);
}

void constructor()
{    
    set_cmd();
    set_arg_list();
    set_io_redirect();
}

void run()
{
    printf("'%s'\n", line.cmd);
    printf("'%s'\n", line.arg_list);
    printf("'%s'\n", line.io_in);
    printf("'%s'\n", line.io_out);

}

int main(int argc, char const *argv[])
{
    putchar('%');
    fgets(buf, BUFSIZ, stdin);

    constructor();
    run();

    return 0;
}