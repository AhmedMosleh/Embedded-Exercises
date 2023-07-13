#include <stdio.h>

#define PI 3.14159
#define area(r) PI*r*r

int main() {
    float radius, a;

    // Ask the user to enter the radius of the circle
    printf("Enter the radius: ");
    scanf("%f", &radius);

    // Calculate the area of the circle using the macro
    a = area(radius);

    // Display the area of the circle
    printf("Area=%.2f", a);

    return 0;
}