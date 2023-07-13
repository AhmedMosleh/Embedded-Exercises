#include <stdio.h>

double power(double base, int exponent);

int main() {
    double base, result;
    int exponent;

    // Ask the user to enter the base number and the power number
    printf("Enter base number: ");
    scanf("%lf", &base);
    printf("Enter power number(positive integer): ");
    scanf("%d", &exponent);

    // Calculate the power of the number using recursion
    result = power(base, exponent);

    // Display the result
    printf("%.2lf^%d: %.2lf", base, exponent, result);

    return 0;
}

// Recursive function to calculate the power of a number
double power(double base, int exponent) {
    if(exponent == 0) {
        return 1;
    }
    else if(exponent % 2 == 0) {
        double temp = power(base, exponent/2);
        return temp * temp;
    }
    else {
        double temp = power(base, (exponent-1)/2);
        return base * temp * temp;
    }
}