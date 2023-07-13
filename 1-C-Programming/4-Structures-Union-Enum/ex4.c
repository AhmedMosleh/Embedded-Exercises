#include <stdio.h>

struct student {
    char name[50];
    int roll;
    float marks;
};

int main() {
    struct student s[10];

    // Ask the user to enter the information of 10 students
    printf("Enter information of students:\n");
    for(int i = 0; i < 10; i++) {
        printf("For roll number %d\n", i+1);
        printf("Enter name: ");
        scanf("%s", s[i].name);
        printf("Enter marks: ");
        scanf("%f", &s[i].marks);
    }

    // Display the information of the students
    printf("\nDisplaying information of students:\n");
    for(int i = 0; i < 10; i++) {
        printf("Information for roll number %d:\n", i+1);
        printf("Name: %s\n", s[i].name);
        printf("Marks: %.2f\n\n", s[i].marks);
    }

    return 0;
}