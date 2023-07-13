#include <stdio.h>

int isPrime(int num);

int main() {
    int start, end, i;

    // Ask the user to enter two numbers (intervals)
    printf("Enter two numbers(intervals): ");
    scanf("%d %d", &start, &end);

    // Display all prime numbers between start and end
    printf("Prime numbers between %d and %d are: ", start, end);
    for(i=start; i<=end; i++) {
        if(isPrime(i)) {
            printf("%d ", i);
        }
    }

    return 0;
}

// Function to check if a number is prime or not
int isPrime(int num) {
    int i;
    if(num <= 1) {
        return 0;
    }
    for(i=2; i*i<=num; i++) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}