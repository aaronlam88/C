#include <stdio.h>
#include <string.h>

int main() {
    char line[1000];
    while ((fgets(line, 1000, stdin)) != NULL) {
        char c = line[0];
        int count = 0;
        int linen = strlen(line);
        for (int i = 0; i < linen; i++) {
            if (line[i] == c) {
                count++;
            } else {
                printf("%d%c", count, c);
                c = line[i];
                count = 1;
            }
        }
        printf("\n");
    }
}
