#include <stdio.h>

int main() {
    char str[100], ch;
    int i, freq = 0;

    // Ask the user to enter a string
    printf("Enter a string: ");
    gets(str);

    // Ask the user to enter the character to find its frequency
    printf("Enter a character to find frequency: ");
    scanf("%c", &ch);

    // Find the frequency of the character in the string
    for(i=0; str[i]!='\0'; i++) {
        if(ch == str[i])
            freq++;
    }

    // Display the frequency of the character in the string
    printf("Frequency of %c = %d", ch, freq);

    return 0;
}