#ifndef MY_STRING_HEADER
#define MY_STRING_HEADER

#include <stddef.h>

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



#endif