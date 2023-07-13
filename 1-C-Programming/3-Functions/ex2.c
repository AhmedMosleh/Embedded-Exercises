#include <stdio.h>

int factorial(int n);

int main() {
    int n;

    // Ask the user to enter a positive integer
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // Calculate the factorial of the integer using recursion
    printf("Factorial of %d = %d", n, factorial(n));

    return 0;
}

// Recursive function to calculate the factorial of a number
int factorial(int n) {
    if(n == 0) {
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}