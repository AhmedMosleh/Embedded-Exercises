#include <stdio.h>

struct Complex {
    float real;
    float imag;
};

struct Complex addComplex(struct Complex c1, struct Complex c2);

int main() {
    struct Complex c1, c2, sum;

    // Ask the user to enter the information for the first complex number
    printf("For 1st complex number\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f %f", &c1.real, &c1.imag);

    // Ask the user to enter the information for the second complex number
    printf("For 2nd complex number\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f %f", &c2.real, &c2.imag);

    // Add the two complex numbers by calling the function addComplex()
    sum = addComplex(c1, c2);

    // Display the sum of complex numbers
    printf("Sum=%.1f+%.1fi", sum.real, sum.imag);

    return 0;
}

// Function to add two complex numbers
struct Complex addComplex(struct Complex c1, struct Complex c2) {
    struct Complex sum;
    sum.real = c1.real + c2.real;
    sum.imag = c1.imag + c2.imag;
    return sum;
}