#include <stdio.h>
#include <string.h>

int atoi(const char* str);
char* itoa(int value, char* str, int base);

int main(int argc, char const *argv[])
{
	char str1[100];
	char str2[100];
	gets(str1);
	int numb = atoi(str1);
	printf("%d\n", numb);
	itoa(numb, str2, 10);
	printf("%s\n", str2);
	if(strcmp(str1, str2) != 0)
		printf("Error\n");
	return 0;
}

int atoi(const char* str)
{
	int toValue = 0, neg = 0, i = 0;
	if(str[0] == '-'){
		neg = 1;
		i = 1;
	}
	for(; str[i]; ++i)
	{
		toValue = (toValue * 10) + str[i] - 48;
	}
	if(neg)
		toValue = 0 - toValue;
	return toValue;
}

char* itoa(int value, char* str, int base)
{
	int i, j, k = value;
	if(k < 0)
		value = -1 * value;
	str[0] = (value % base) + 48;
	for (i = 1; (value/=10) != 0;  ++i)
	{
		str[i] = (value % base) + 48;
	}
	if(k < 0)
		str[i++] = '-';
	str[i] = '\0';
	--i;
	for (int j = 0; j < i; ++j, --i){
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}