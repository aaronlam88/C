/*********************************************************************/
/*  Author: Aaron Lam                                                */
/*  SID: 92329177 Class ICS 53                                       */
/*  Description: Learn about signal handling                         */
/*            print I for ^C, Q for ^\, and S for ^Z                 */
/*            after 3 ^Z, print out all the number to signal and exit*/
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static int interrupt = 0;
static int stop = 0;
static int quit = 0;

void _before_stop()
{
    printf("\n");
    printf("Interrupt: %d\n", interrupt);
    printf("Stop: %d\n", stop);
    printf("Quit: %d\n", quit);
    exit(0);
}

void int_handler(int sig)
{
    ++interrupt;
    putchar('I');
    fflush(stdout);
    return;
}

void quit_handler(int sig)
{
    ++quit;
    putchar('Q');
    fflush(stdout);
    return;
}

void tstp_handler(int sig)
{
    ++stop;
    putchar('S');
    fflush(stdout);
    if(stop == 3) _before_stop();
    signal(SIGTSTP, SIG_DFL);
    raise(SIGTSTP);
}

void cont_handler (int sig)
{
  signal (SIGCONT, cont_handler);
  signal (SIGTSTP, tstp_handler);
}

static void init_signal_handlers()
{
    signal(SIGINT, int_handler);
    signal(SIGQUIT, quit_handler);
    signal(SIGTSTP, tstp_handler);
    signal(SIGCONT, cont_handler);
}

void _print()
{
    while(1)
    {
        printf("X");
        sleep(1);
        fflush(stdout);
    }
}

int main(int argc, char const *argv[])
{
    setbuf(stdout, NULL);
    init_signal_handlers();
    _print();

    return 0;
}
