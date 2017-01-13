#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
	FILE* fp = fopen(argv[1], "r");
	int c = getchar();
	putchar(c);
	return 0;
}