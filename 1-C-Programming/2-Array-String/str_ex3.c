#include <stdio.h>
#include <string.h>

int main() {
    char str[100], temp;
    int i, j, length;

    // Ask the user to enter a string
    printf("Enter the string ");
    gets(str);

    // Find the length of the string
    length = strlen(str);

    // Reverse the string
    for(i=0, j=length-1; i<j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    // Display the reversed string
    printf("Reverse string is %s", str);

    return 0;
}