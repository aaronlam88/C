#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>
#include <ctype.h>

int main() {
    char line[1000];
    while ((fgets(line, 1000, stdin)) != NULL) {
        char num[25];
        int index = 0;
        char c;
        int linen = strlen(line);
        for (int i = 0; i < linen; i++) {
            if (isalpha(line[i])) {
                c = line[i];
                strncpy(num, &line[index], i - index);
                num[i-index] = 0;
                int n = atoi(num);
                for (int j = 0; j < n; j++) {
                    printf("%c", c);
                }
                index = i+1;
            }
        }
        printf("\n");
    }
}
