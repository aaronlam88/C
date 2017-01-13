//=====================================================================
// Do Reverse Polish notation calculation
//=====================================================================
#include <stdio.h>
#include <string.h>
#include "stk.h"

#define MAX_BUFF 1024

void print()
{
    if(stk_is_empty())
        return;
    ELE temp = stk_pop();
    printf("%s\n", temp.buf);
    stk_push(temp);
}

void swap()
{
    if(stk_is_empty())
        return;
    ELE temp1 = stk_pop();
    if(stk_is_empty())
    {
        stk_push(temp1);
        return;
    }
    ELE temp2 = stk_pop();
    stk_push(temp1);
    stk_push(temp2);
}

void duplicate()
{
    if(stk_is_empty())
        return;
    ELE temp = stk_pop();
    stk_push(temp);
    stk_push(temp);
}

void add()
{
    long long a, b;
    ELE temp1 = stk_pop();
    ELE temp2 = stk_pop();
    a = atoll(temp1.buf);
    b = atoll(temp2.buf);
    //printf("%f %f\n", a, b);
    ELE c = make_element(b + a);
    //printf("Add = %d\n", a + b);
    stk_push(c);
}

void subtract()
{
    long long a, b;
    ELE temp1 = stk_pop();
    ELE temp2 = stk_pop();
    a = atoll(temp1.buf);
    b = atoll(temp2.buf);
    ELE c = make_element(b - a);
    //printf("Subtract = %d\n", b - a);
    stk_push(c);
}

void multiply()
{
    long long a, b;
    ELE temp1 = stk_pop();
    ELE temp2 = stk_pop();
    a = atoll(temp1.buf);
    b = atoll(temp2.buf);
    ELE c = make_element(b * a);
    //printf("multiplied = %d\n", b * a);
    stk_push(c);
}

void divide()
{
    long long a, b;
    ELE temp1 = stk_pop();
    ELE temp2 = stk_pop();
    a = atoll(temp1.buf);
    b = atoll(temp2.buf);
    ELE c = make_element(b / a);
    //printf("divide = %d\n", b/a);
    stk_push(c);
}

void push_e(char * token)
{
    long long i = atoll(token);
    ELE e = make_element(i);
    stk_push(e);
}

void process_token(char *token)
{
    if(token == NULL)
        return;
    if(isdigit(token[strlen(token)-1]))
    {
        push_e(token);
        return;
    }
    //printf("TOKEN = %s\n", token);
    switch(token[0])
    {
        case 'p':
            print();
            break;
        case 's':
            swap();
            break;
        case 'd':
            duplicate();
            break;
        case '+':
            add();
            break;
        case '-':
            subtract();
            break;
        case '*':
            multiply();
            break;
        case '/':
            divide();
            break;
    }
}


void getInput()
{
    char buff[MAX_BUFF];
    fgets(buff, MAX_BUFF, stdin);
    char *tok = strtok(buff, " ");
    push_e(tok);
    while(tok != NULL)
    {
        tok = strtok(NULL, " \n");
        process_token(tok);
    }
}

int main(int argc, char *argv[])
{
    getInput();
    return 0;
}
