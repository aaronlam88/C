//=====================================================================
// Program to print all prime factors
//=====================================================================
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

#define MAX_PRIME_ARRAY_SIZE 1024

void print_prime(int prime[])
{
    printf("%d", prime[0]);
    for(int i = 1; prime[i] != 0 ; ++i)
        printf(" x %d", prime[i]);
    printf("\n");
}
 
// A function to print all prime factors of a given number n
void primeFactors(int n, int prime[])
{
    printf("Prime factorization of %d is ", n);
    int index = 0;

    // Print the number of 2s that divide n
    while (n%2 == 0)
    {
        prime[index++] = 2;
        n = n/2;
    }
 
    // n must be odd at this point.  So we can skip one element
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        // While i divides n, print i and divide n
        while (n%i == 0)
        {
            prime[index++] = i;
            n = n/i;
        }
    }
 
    // This condition is to handle the case when n is a prime number greater than 2
    if (n > 2)
        prime[index] =  n;
    print_prime(prime, index);
}

 
/* Driver program to test above function */
int main(int argc, char const *argv[])
{
    int prime[MAX_PRIME_ARRAY_SIZE];
    for(int i = 1; i < argc; ++i)
    {
        int j = atoi(argv[i]);
        primeFactors(j, prime);
    }
    return 0;
}
