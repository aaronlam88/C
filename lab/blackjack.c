#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char suits[4][1] = {"S", "H", "D", "C"};
char cards[13][1] = {"A", "K", "Q", "J", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
char deck[52][3];

int handValue(char hand[][2], int size) {
    int sum = 0;
    int aces = 0;
    for(int i = 0; i < size; i++)
    {
        if (isalpha(hand[i][0]))  {
            if (hand[i][0] == 'A') {
                aces++;
                sum = sum + 11;
            } else {
                sum = sum + 10;
            }
        } else {
            sum = sum + hand[i][0] - 47;
        }
    }
    for (int i = 0; i < aces; i++) {
        if (sum > 21) sum = sum - 10;
    }
    return sum;
}

void shuffle(char d[52][2]) {
    for (int i = 0; i < 52; i++) {
        strcpy(d[i], "0\0");
        printf("%s\n", d[i]);
    }
    srand(time(NULL));
    int r = rand();
    for (int i = 0; i < 52; i++) {
        int index = atoi(deck[i]) * r % 52;
        while (strcmp(d[index], "0") != 0) {
            index++;
            if (index == 52) index = 0;
        }
        strcpy(d[index], deck[i]);
    }
}

int main() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[i*4+j][0] = cards[i][0];
            deck[i*4+j][1] = suits[j][0];
            deck[i*4+j][2] = 0;
        }
    }
    char d[52][2];
    shuffle(d);
    for (int i = 0; i < 52; i++) {
        printf("%s\n", d[i]);
    }
    return 0;
}
