/*
 * Author: Aaron Lam
 * Program discrition: implemention of string.h functions
 * For: Class: ICS 53
 * Last update: 01/21/2016
 */

#include <stdio.h>

#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)

// my_str functions declaration  
static char *tok = NULL;

size_t  my_strlen      (const char  *str); //tested

char    *my_strchr     (const char  *str,   int c); //tested
char    *my_strrchr    (const char  *str,   int c); //tested

char    *my_strcat     (char        *dest,  const char *src); //tested
char    *my_strncat    (char        *dest,  const char *src, size_t n); //tested

char    *my_strcpy     (char        *dest,  const char *src); //tested
char    *my_strncpy    (char        *dest,  const char *src, size_t n); //tested

int     my_strcmp      (const char  *str1,  const char *str2); //tested
int     my_strncmp     (const char  *str1,  const char *str2, size_t n); //tested

size_t  my_strspn      (const char  *str1,  const char *str2);
size_t  my_strcspn     (const char  *str1,  const char *str2); //tested

char    *my_strpbrk    (const char  *str1,  const char *str2); //tested

char    *my_strstr     (const char  *haystack, const char *needle);

char    *my_strtok     (char        *str,   const char *delim);
//--------------------------------------------------------------------

// my_str funtions definition
// Computes the length of the string str up to but not including the terminating null character.
size_t my_strlen(const char *str)
{
    size_t i;

    for(i = 0; str[i] ; ++i)
        ;
    return i;
}

// Searches for the first occurrence of the character c (an unsigned char) 
//in the string pointed to, by the argument str.
char *my_strchr(const char *str, int c)
{
    do
    {
        if(*str == c)
            return (char*) str;
    }while(*str++);
    return 0;
}

// Searches for the last occurrence of the character c (an unsigned char) 
// in the string pointed to by the argument str.
char *my_strrchr(const char *str, int c)
{
    char *p = NULL;

    for(; *str ; ++str)
    {
        if(*str == c)
            p = (char*) str;
    }
    return p;
}


// Appends the string pointed to, by src to the end of the string pointed to by dest.
char *my_strcat(char *dest, const char *src)
{
    size_t i , dest_len = my_strlen(dest);

    for(i = 0; src[i] ; ++i)
        dest[dest_len++] = src[i];
    dest[dest_len] = '\0';
    return dest;
}

// Appends the string pointed to, by src to the end of the string pointed to 
// by dest up to n characters long.
char *my_strncat(char *dest, const char *src, size_t n)
{
    size_t i, dest_len = my_strlen(dest);

    for(i = 0; src[i]  && i < n ; ++i)
        dest[dest_len++] = src[i];
    dest[dest_len] = '\0';
    return dest;
}

// Copies the string pointed to, by src to dest.
char *my_strcpy(char *dest, const char *src)
{
    size_t i;

    for(i = 0; src[i] ; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

// Copies up to n characters from the string pointed to, by src to dest.
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for(i = 0; i < n; ++i){
        dest[i] = src[i];
        if(src[i] == '\0')
            break;
    }
    
    return dest;
}


// Compares the string pointed to, by str1 to the string pointed to by str2.
int my_strcmp(const char *str1, const char *str2)
{
    size_t i;

    for(i = 0; str1[i] == str2[i] && str1[i]  && str2[i] ; ++i)
        ;
    return str1[i] - str2[i];
}

// Compares at most the first n bytes of str1 and str2.
int my_strncmp(const char *str1, const char *str2, size_t n)
{
    size_t i;

    for(i = 0; str1[i] == str2[i] && str1[i] && str2[i]  && i < n-1; ++i)
        ;//loop to i < n -1 because returning the difference of last char
    return str1[i] - str2[i];
}

// Calculates the length of the initial segment of str1 
// which consists entirely of characters in str2.
size_t my_strspn(const char *str1, const char *str2)
{
    size_t i;

    for(i = 0; str1[i] ; ++i)
    {
        if(my_strchr(str2, str1[i]) == 0)
            return i;
    }
    return i;

}

// Calculates the length of the initial segment of str1 
// which consists entirely of characters not in str2.
size_t my_strcspn(const char *str1, const char *str2)
{
    size_t i;

    for(i = 0; str1[i] ; ++i)
    {
        if(my_strchr(str2, str1[i]) != 0)
            return i;
    }
    return i;
}



// Finds the first character in the string str1 that 
// matches any character specified in str2.
char *my_strpbrk(const char *str1, const char *str2)
{
    size_t i;
    for( ; *str1; str1++ ) 
    {
        for(i = 0; str2[i] ; ++i) 
        {
            if(str2[i] == *str1) 
                return (char*)str1;
        }
    }
    return 0;
}

// Finds the first occurrence of the entire string needle 
// (not including the terminating null character) which appears in the string haystack.
char *my_strstr(const char *haystack, const char *needle)
{
    size_t n = my_strlen(needle);
    for(; *haystack ; ++haystack)
    {
        if(my_strncmp(haystack, needle, n) == 0)
            return (char *) haystack;
    }
    return 0;
}

// Private function use by strtok()
char *has_more(char *start, size_t end)
{
    if(start[end] == '\0')
        return NULL;
    else
    {
        start[end] = '\0';
        return &start[end + 1];
    }
}
char *get_token(char *start, const char *delim)
{
    size_t i;

    for(; *start && my_strchr(delim, *start) != NULL; ++start)
        ;
    for(i = 0; start[i] && my_strchr(delim, start[i]) == NULL; ++i)
        ;
    return has_more(start, i);
}
// Breaks string str into a series of tokens separated by delim.
char *my_strtok(char *str, const char *delim)
{
    char *start;

    str != NULL ? (start = str) : (start = tok);
    if(start == NULL)
        return NULL;
    tok = get_token(start, delim);
    return start;
}

void test_strlen()
{
    printf("test_strlen...");
    require(my_strlen("") == 0);
    require(my_strlen("hello") == 5);
    printf("end_test\n");
}

void test_strchr()
{
    printf("test_strchr...");
    const char str[] = "http://www.tutorialspoint.com";

    require(my_strchr(str, ' ') == NULL);
    require(my_strchr(str, 'z') == 0);
    require(my_strcmp(my_strchr(str, 'h'), "http://www.tutorialspoint.com") == 0);
    require(my_strcmp(my_strchr(str, '.'), ".tutorialspoint.com") == 0);

    printf("end_test\n");
}

void test_strrchr()
{
    printf("test_strrchr...");
    const char str[] = "http://www.tutorialspoint.com";

    require(my_strrchr(str, ' ') == NULL);
    require(my_strrchr(str, 'z') == 0);
    require(my_strcmp(my_strrchr(str, 't'), "t.com") == 0);
    require(my_strcmp(my_strrchr(str, '.'), ".com") == 0);

    printf("end_test\n");
}

void test_strcat()
{
    printf("test_strcat...");
    char dest [100] = "";
    const char *str1 = "Hello", *str2 = "World";

    my_strcat(dest, str1);
    require(my_strcmp(dest, "Hello") == 0);
    my_strcat(dest, str2);
    require(my_strcmp(dest, "HelloWorld") == 0);

    printf("end_test\n");
}

void test_strncat()
{
    printf("test_strncat...");
    char dest [100] = "";
    const char *str1 = "Hello", *str2 = "World";

    my_strncat(dest, str1, 10);
    require(my_strcmp(dest, "Hello") == 0);
    my_strncat(dest, str2, 3);
    require(my_strcmp(dest, "HelloWor") == 0);

    printf("end_test\n");
}

void test_strcpy()
{
    printf("test_strcpy...");
    char dest [100];

    require(my_strcmp(my_strcpy(dest, "Hello"), "Hello") == 0);
    require(my_strcmp(my_strcpy(dest, "Hello World"), "Hello World") == 0);
    require(my_strcmp(my_strcpy(dest, ""), "") == 0);
    
    printf("end_test\n");
}

void test_strncpy()
{
    printf("test_strncpy...");
    char dest [100];

    my_strncpy(dest, "Hello", 4);
    dest[4] = '\0';//add '\0'
    require(my_strcmp(dest, "Hell") == 0);
    require(my_strcmp(my_strncpy(dest, "World", 6), "World") == 0); //6; because "World\0"
    require(my_strcmp(my_strncpy(dest, "Hello World", 100), "Hello World") == 0);
    
    printf("end_test\n");
}

void test_strcmp()
{
    printf("test_strcmp...");
    const char *r = "hello", *s = "hello", *t = "he";

    require(my_strcmp(r,s) == 0);
    require(my_strcmp(t,r) < 0);
    require(my_strcmp(s,t) > 0);

    printf("end_test\n");
}

void test_strncmp()
{
    printf("test_strncmp...");
    const char *r = "hello", *s = "hello", *t = "he";

    require(my_strncmp(r,s, 4) == 0);
    require(my_strncmp(t,r, 2) == 0);
    require(my_strncmp(s,t, 4) > 0);

    printf("end_test\n");
}

void test_strspn()
{
    printf("test_strspn...");

    require(my_strspn("ABCDEFG019874", "ABCD") == 4);
    require(my_strspn("ABCDEF4960910", "013") == 0);
    require(my_strspn("129th", "1234567890") == 3);

    printf("end_test\n");
}

void test_strcspn()
{
    printf("test_strcspn...");

    require(my_strcspn("ABCDEFG019874", "2016") == 7);
    require(my_strcspn("ABCDEF4960910", "013") == 9);
    require(my_strcspn("129th", "1234567890") == 0);

    printf("end_test\n");
}


void test_strpbrk()
{
    printf("test_strpbrk...");
    const char str1[] = "abcde2fghi3jk4l";

    require(*my_strpbrk(str1, "a") == 'a');
    require(my_strcmp(my_strpbrk(str1, "a"), "abcde2fghi3jk4l") == 0);
    require(my_strcmp(my_strpbrk(str1, "test"), "e2fghi3jk4l") == 0);
    require(my_strpbrk(str1, "z")== NULL);

    printf("end_test\n");
}

void test_strstr()
{
    printf("test_strstr...");

    require(my_strcmp(my_strstr("haystack", "stack"), "stack") == 0);
    require(my_strstr("haystack", "needle") == NULL);
    require(my_strcmp(my_strstr("My House is small", "House"), "House is small") == 0);
    require(my_strcmp(my_strstr("My Car is green", "My Car"), "My Car is green") == 0);

    printf("end_test\n");
}

void test_strtok()
{
    printf("test_strtok...");
    char str[] = "This is|token;string";

    require(my_strcmp(my_strtok(str, " |;"), "This") == 0);
    require(my_strcmp(my_strtok(NULL, " |;"), "is") == 0);
    require(my_strcmp(my_strtok(NULL, " |;"), "token") == 0);
    require(my_strcmp(my_strtok(NULL, " |;"), "string") == 0);
    require(my_strtok(NULL, " |;") == NULL);

    printf("end_test\n");
}

int main()
{
    printf("Start Test\n");

    test_strlen();

    test_strchr();
    test_strrchr();
    
    test_strcmp();
    test_strncmp();

    test_strcat();
    test_strncat();

    test_strcpy();
    test_strncpy();

    test_strspn();
    test_strcspn();

    test_strpbrk();

    test_strstr();

    test_strtok();
    
    printf("End Test\n");
    return 0;
}