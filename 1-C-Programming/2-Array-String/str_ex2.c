#include <stdio.h>

int main() {
    char str[100];
    int i, length = 0;

    // Ask the user to enter a string
    printf("Enter a string: ");
    gets(str);

    // Find the length of the string
    for(i=0; str[i]!='\0'; i++)
        length++;

    // Display the length of the string
    printf("Length of string: %d", length);

    return 0;
}