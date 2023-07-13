#include <stdio.h>

int main() {
    int n, i;
    double sum = 0, average;
    
    // Ask the user to enter the number of data
    printf("Enter the number of data: ");
    scanf("%d", &n);
    
    double data[n];
    
    // Ask the user to enter the data
    for (i = 0; i < n; i++) {
        printf("%d. Enter number: ", i+1);
        scanf("%lf", &data[i]);
        sum += data[i];
    }
    
    // Calculate the average
    average = sum / n;
    
    // Display the average
    printf("Average = %.2lf", average);
    
    return 0;
}