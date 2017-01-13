#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ROWS 22
#define COLS 81

int INC_X[8] = {1, 1, 0, -1, -1, -1, 0, 1}, INC_Y[8] = {0, -1, -1, -1, 0, 1, 1, 1};
char BUFFER[ROWS * COLS + 1];

int flush_buffer();

int setBuf(int r, int c, int v)
{
    BUFFER[r * COLS + c] = v;
}

int getBuf(int r, int c)
{
    return BUFFER[r * COLS + c];
}

int init_buffer()
{
    int i = 0, r = 0, c = 0, randnum = 0;
    memset(BUFFER, ' ', ROWS*COLS);
    for (; i < ROWS; ++i) setBuf(i, COLS - 1, '\n');
    for (; r < ROWS; ++r)
        for (c = 0; c < COLS-1; ++c) 
        {
            randnum = rand();
            setBuf(r, c, (randnum<(RAND_MAX/5))?'A':' ');
        }
}

int flush_buffer()
{
    sleep(1);
    int i = 0;
    printf("\x1B[0;0H%s", BUFFER);
}

int count_neighbor(int r, int c)
{
    int i = 0, x = 0, y = 0, sum = 0;
    for (; i < 8; ++i)
    {
        x = INC_X[i] + r; y = INC_Y[i] + c;
        if ( !(x<0||x>ROWS-1||y<0||y>=COLS-1) ) sum = (getBuf(x, y)!=' ')?(sum+1):sum;
    }
}

int exec_cell(r, c)
{
    int sum = count_neighbor(r, c);
    if ( getBuf(r, c) != ' ') 
    {
        if (sum < 2) setBuf(r, c, ' ');
        else if (sum > 3) setBuf(r, c, ' ');
    }
    else if (sum == 3) setBuf(r, c, 'A');
}

int update_cells()
{
    int r = 0, c = 0;
    for (; r < ROWS; ++r) for ( c = 0; c < COLS-1; ++c) exec_cell(r, c);
}

int main_loop()
{
    int i = 0, j = 0;
    for (;;)
    {
        update_cells();
        flush_buffer();
    }
}

int main()
{
    init_buffer();
    main_loop();
    return 0;
}
