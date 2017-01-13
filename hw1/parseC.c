#include <stdio.h>
#include <ctype.h>
#include <string.h>

static char in;
static char buff[256]; //input buffer
static int curr = 0; //current location in buffer

void start_state();
void switch_state(char c);
void comment_state();
void singleline_comment_state();
void multiline_commend_state();
void isalnum_state(char c);
void non_alpha_state(char c);
void quote_state();
void char_state();
void single_char_state();
void second_char_state(char c);

void print();

void print()
{
    buff[curr++] = '\0';
    printf("%s\n", buff);
    curr = 0;
}

void start_state()
{
    char c = getchar();
    if(c == EOF)
        return;
    else
        switch_state(c);
}

void switch_state(char c)
{
    if(isalnum(c))
        isalnum_state(c);
    else
        non_alpha_state(c);
}

void comment_state()
{
    char c = getchar();
    switch(c)
    {
        case '/': singleline_comment_state(); break;
        case '*': multiline_commend_state(); break;
    }

}

void singleline_comment_state()
{
    while(getchar() != '\n');
    start_state();
}

void multiline_commend_state()
{
    char c;
    for(c = getchar(); c != '*'; c = getchar())
        ;
    c = getchar();
    c == '/' ? start_state() : multiline_commend_state();
}

void isalnum_state(char c)
{
    for(; isalnum(c) || c == '_'; c = getchar())
        buff[curr++] = c;
    print();
    ungetc(c, stdin);
    start_state();
}

void quote_state()
{
    char c = '\"';
    buff[curr++] = c;
    for(c = getchar(); c != '\"' ; c = getchar())
    {
        buff[curr++] = c;
        c == '\\' ? buff[curr++] = getchar() : c;
    }
    buff[curr++] = c;
    print();
    start_state();
}

void single_char_state()
{
    char c = getchar();
    getchar();
    printf("'%c'\n", c);
}

void second_char_state(char c)
{
    char c2 = getchar();
    if(c == c2 || c2 == '=')
        printf("%c%c\n", c, c2);
    else
    {
        printf("%c\n", c);
        ungetc(c2, stdin);
    }

}

void non_alpha_state(char c)
{
    switch(c)
    {
        case '\n':
        case ' ' :                          break;
        case '/' : comment_state();         break;
        case '\"' : quote_state();          break;
        case '\'': single_char_state();     break;
        case '+' : second_char_state('+');  break;
        case '-' : second_char_state('-');  break;
        case '=' : second_char_state('=');  break;
        default  : printf("%c\n", c);
    }

    start_state();
}

int main(int argc, char const *argv[])
{
    start_state();
    return 0;
}