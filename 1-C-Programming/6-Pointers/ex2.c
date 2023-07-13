#include <stdio.h>

int main() {
    char *ptr;
    char ch = 'A';

    ptr = &ch;

    // Print all the alphabets using a pointer
    printf("The Alphabets are :\n");
    for (int i = 0; i < 26; i++) {
        printf("%c ", *ptr);
        (*ptr)++;
    }

    return 0;
}