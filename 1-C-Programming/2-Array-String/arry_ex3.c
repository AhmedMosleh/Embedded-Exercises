#include <stdio.h>

int main() {
    int rows, cols, i, j;
    
    // Ask the user to enter the number of rows and columns
    printf("Enter rows and columns of matrix: ");
    scanf("%d %d", &rows, &cols);
    
    int matrix[rows][cols], transpose[cols][rows];
    
    // Ask the user to enter the elements of the matrix
    printf("Enter elements of matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Enter element a%d%d: ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // Find the transpose of the matrix
    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            transpose[i][j] = matrix[j][i];
        }
    }
    
    // Display the original matrix
    printf("\nEntered Matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Display the transpose of the matrix
    printf("\nTranspose of Matrix:\n");
    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}