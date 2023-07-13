#include <stdio.h>

int main() {
    int m = 29;
    int *ab;

    // Display the address and value of m
    printf("Address of m : %p\n", &m);
    printf("Value of m : %d\n", m);

    // Assign the address of m to pointer variable ab
    ab = &m;

    // Display the address and content of pointer variable ab
    printf("Now ab is assigned with the address of m.\n");
    printf("Address of pointer ab : %p\n", ab);
    printf("Content of pointer ab : %d\n", *ab);

    // Change the value of m using pointer variable ab
    *ab = 34;

    // Display the address and content of pointer variable ab
    printf("The value of m assigned to 34 now.\n");
    printf("Address of pointer ab : %p\n", ab);
    printf("Content of pointer ab : %d\n", *ab);

    // Change the value of pointer variable ab
    *ab = 7;

    // Display the address and value of m
    printf("The pointer variable ab is assigned with the value 7 now.\n");
    printf("Address of m : %p\n", &m);
    printf("Value of m : %d\n", m);

    return 0;
}