// =====================================================================
// Author: Aaron Lam                                                
// Description:Calculate forward and backward product of an interger
//             array (input by user)                                
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int size;
static char inputString[BUFSIZ];
static int input[BUFSIZ];
static int forward[BUFSIZ];
static int backward[BUFSIZ];
static int result[BUFSIZ];

void get_input();
void _parse_input();
void forward_product();
void backward_product();
void print_result();

void get_input()
{
    fputs("Please enter your input string\n", stdout);
    fputs("Separate by comma or space: ", stdout);
    fgets(inputString, BUFSIZ, stdin);
    _parse_input();
}

void _parse_input()
{   
    int i;
    char *token = strtok(inputString, " ,\n");
    for(i = 0; i < BUFSIZ && token != NULL; ++i)
    {
        input[i] = atoi(token);
        token = strtok(NULL, " ,\n");
    }
    size = i;
}

void forward_product()
{
    int i;
    for(i = 0; i < size; ++i)
    {
        if(i == 0 || i == (size - 1))
        {
            forward[i] = input[i];
        }
        else
        {
            forward[i] = forward[ i- 1 ] * input[i];
        }
    }
}

void backward_product()
{
    int i = size - 1;
    for( ; i >= 0; --i)
    {
        if(i == 0 || i == (size - 1))
        {
            backward[i] = input[i];
        }
        else
        {
            backward[i] = backward[i + 1] * input[i];
        }
    }
}

void compute()
{
    int i;
    for(i = 0; i < size; ++i)
    {
        if(i == 0)  
            result[i] = backward[i + 1];
        else if(i == size -1) 
            result[i] = forward[i - 1];
        else
            result[i] = forward[i-1] * backward[i+1];
    }
}

void print_result()
{
    int i;
    fputs("Result array: ", stdout);
    for(i = 0; i < size; ++i)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    get_input();
    forward_product();
    backward_product();
    compute();
    print_result();
    return 0;
}


