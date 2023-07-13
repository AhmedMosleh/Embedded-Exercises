#include <stdio.h>

struct student {
    char name[50];
    int roll;
    float marks;
};

int main() {
    struct student s;

    // Ask the user to enter the information of the student
    printf("Enter information of students:\n");
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    // Display the information of the student
    printf("\nDisplaying Information\n");
    printf("name: %s\n", s.name);
    printf("Roll: %d\n", s.roll);
    printf("Marks: %.2f", s.marks);

    return 0;
}