#include <stdio.h>

int main() {
    double matrix1[2][2], matrix2[2][2], sum[2][2];
    int i, j;
    
    // Ask the user to enter elements of matrix 1
    printf("Enter the elements of the 1st matrix\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("Enter a%d%d: ", i+1, j+1);
            scanf("%lf", &matrix1[i][j]);
        }
    }
    
    // Ask the user to enter elements of matrix 2
    printf("Enter the elements of the 2nd matrix\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("Enter b%d%d: ", i+1, j+1);
            scanf("%lf", &matrix2[i][j]);
        }
    }
    
    // Add the two matrices
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    
    // Display the sum of the two matrices
    printf("Sum of matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%.1lf ", sum[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}