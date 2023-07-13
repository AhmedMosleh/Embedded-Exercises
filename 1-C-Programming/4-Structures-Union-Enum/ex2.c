#include <stdio.h>

struct Distance {
    int feet;
    float inch;
};

int main() {
    struct Distance d1, d2, sum;

    // Ask the user to enter the information for the first distance
    printf("Enter information for 1st distance\n");
    printf("Enter feet: ");
    scanf("%d", &d1.feet);
    printf("Enter inch: ");
    scanf("%f", &d1.inch);

    // Ask the user to enter the information for the second distance
    printf("Enter information for 2nd distance\n");
    printf("Enter feet: ");
    scanf("%d", &d2.feet);
    printf("Enter inch: ");
    scanf("%f", &d2.inch);

    // Add the two distances
    sum.feet = d1.feet + d2.feet;
    sum.inch = d1.inch + d2.inch;

    // If the sum of inches is greater than or equal to 12, convert it to feet and inches
    if(sum.inch >= 12.0) {
        sum.inch -= 12.0;
        sum.feet++;
    }

    // Display the sum of distances
    printf("\nSum of distances=%d\'-%.1f\"", sum.feet, sum.inch);

    return 0;
}