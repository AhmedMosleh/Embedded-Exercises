#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

struct employee {
    char name[30];
    int id;
};

int main() {
    struct employee *emp[MAX_SIZE];
    struct employee e1 = {"Alex", 1002};
    emp[0] = &e1;

    // Print the employee name and ID using the pointer to array of pointers
    printf("Employee Name : %s\n", emp[0]->name);
    printf("Employee ID : %d\n", emp[0]->id);

    return 0;
}