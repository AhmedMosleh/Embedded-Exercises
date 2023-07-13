#include <stdio.h>

void reverseSentence();

int main() {
    printf("Enter a sentence: ");
    reverseSentence();

    return 0;
}

// Recursive function to reverse a sentence
void reverseSentence() {
    char c;
    scanf("%c", &c);

    if(c != '\n') {
        reverseSentence();
        printf("%c", c);
    }
}