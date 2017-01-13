#include <stdio.h>

#include "my_string.h"

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