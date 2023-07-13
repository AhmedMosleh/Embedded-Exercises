#include <stdio.h>

int main() {
    int n, i, num, loc;
    
    // Ask the user to enter the number of elements in the array
    printf("Enter no of elements: ");
    scanf("%d", &n);
    
    int arr[n+1];
    
    // Ask the user to enter the elements of the array
    printf("Enter the elements of the array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Ask the user to enter the element to be inserted and its location
    printf("Enter the element to be inserted: ");
    scanf("%d", &num);
    printf("Enter the location: ");
    scanf("%d", &loc);
    
    // Shift the elements to the right of the insertion point to make space for the new element
    for (i = n; i >= loc; i--) {
        arr[i] = arr[i-1];
    }
    
    // Insert the new element at the specified location
    arr[loc-1] = num;
    
    // Display the updated array
    printf("Updated array: ");
    for (i = 0; i < n+1; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}