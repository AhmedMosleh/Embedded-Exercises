#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main() {
    char str[MAX_SIZE], *ptr;
    int len;

    // Take input from the user
    printf("Input a string : ");
    fgets(str, MAX_SIZE, stdin);

    // Remove the newline character from the input string
    len = strlen(str);
    if (str[len-1] == '\n') {
        str[len-1] = '\0';
    }

    // Print the input string in reverse using a pointer
    printf("Reverse of the string is : ");
    ptr = str + len - 1;
    while (ptr >= str) {
        printf("%c", *ptr);
        ptr--;
    }

    return 0;
}