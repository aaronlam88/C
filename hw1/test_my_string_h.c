#include <stdio.h>
#include "my_string.h"

#include <string.h>

#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)

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