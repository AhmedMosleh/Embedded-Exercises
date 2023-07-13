#include <stdio.h>

#define MAX_SIZE 15

int main() {
    int arr[MAX_SIZE];
    int i, n;

    // Take input from the user
    printf("Input the number of elements to store in the array (max %d) : ", MAX_SIZE);
    scanf("%d", &n);

    printf("Input %d number of elements in the array :\n", n);
    for (i = 0; i < n; i++) {
        printf("element -%d : ", i+1);
        scanf("%d", &arr[i]);
    }

    // Print the elements of the array in reverse order
    printf("\nThe elements of array in reverse order are :\n");
    for (i = n-1; i >= 0; i--) {
        printf("element -%d : %d\n", i+1, arr[i]);
    }

    return 0;
}