#include <stdio.h>

int main() {
    int n, i, search, arr[100], flag = 0;

    // Ask the user to enter the number of elements in the array
    printf("Enter no of elements: ");
    scanf("%d", &n);

    // Ask the user to enter the elements of the array
    printf("Enter %d elements: ", n);
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);

    // Ask the user to enter the element to be searched
    printf("Enter the element to be searched: ");
    scanf("%d", &search);

    // Search for the element in the array
    for(i=0; i<n; i++) {
        if(arr[i] == search) {
            printf("Number found at the location = %d", i+1);
            flag = 1;
            break;
        }
    }

    // Display a message if the element is not found
    if(flag == 0)
        printf("Number not found");

    return 0;
}