#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define FILE_NAME "students.dat"

// 1. Structure to store student details
struct Student {
    int rollNo;
    char name[50];
    float marks[3];
    float total;
    float average;
};

// Function prototypes using pointers
void calculateResult(struct Student *s);
void addStudents(struct Student *students, int *count);
void displayStudents(const struct Student *students, int count);
void searchStudent(const struct Student *students, int count, int rollNo);
void saveToFile(const struct Student *students, int count);
void loadFromFile(struct Student *students, int *count);

int main() {
    // 2. Array of structures (supports at least 5, up to 50 students)
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice, searchRoll;

    // Load any existing records from the file on startup
    loadFromFile(students, &count);

    do {
        printf("\n=== Student Record & Result Management System ===\n");
        printf("1. Add Student Records\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Save Records to File\n");
        printf("5. Retrieve & Display Records from File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // Clear invalid non-integer input
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                addStudents(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                printf("Enter Roll Number to search: ");
                scanf("%d", &searchRoll);
                searchStudent(students, count, searchRoll);
                break;
            case 4:
                saveToFile(students, count);
                break;
            case 5:
                loadFromFile(students, &count);
                displayStudents(students, count);
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// 3 & 4. Function using a pointer to calculate total and average marks
void calculateResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < 3; i++) {
        s->total += s->marks[i];
    }
    s->average = s->total / 3.0f;
}

// Function to add student records using pointers
void addStudents(struct Student *students, int *count) {
    int n;
    printf("How many students do you want to add? (Recommended at least 5): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a valid positive number.\n");
        return;
    }

    if (*count + n > MAX_STUDENTS) {
        printf("Cannot exceed maximum limit of %d students.\n", MAX_STUDENTS);
        return;
    }

    for (int i = 0; i < n; i++) {
        struct Student *current = &students[*count];
        printf("\n--- Enter Details for Student %d ---\n", *count + 1);

        printf("Roll Number: ");
        scanf("%d", &current->rollNo);

        printf("Name: ");
        scanf(" %49[^\n]", current->name);

        for (int j = 0; j < 3; j++) {
            printf("Marks in Subject %d: ", j + 1);
            scanf("%f", &current->marks[j]);
        }

        calculateResult(current);
        (*count)++;
    }

    printf("\nStudent record(s) added successfully!\n");
}

// Function to display all student records
void displayStudents(const struct Student *students, int count) {
    if (count == 0) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n",
           "Roll No", "Name", "Sub 1", "Sub 2", "Sub 3", "Total", "Average");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        const struct Student *s = &students[i];
        printf("%-10d %-20s %-8.2f %-8.2f %-8.2f %-10.2f %-10.2f\n",
               s->rollNo, s->name, s->marks[0], s->marks[1], s->marks[2], s->total, s->average);
    }
}

// Function to search a student by roll number
void searchStudent(const struct Student *students, int count, int rollNo) {
    for (int i = 0; i < count; i++) {
        const struct Student *s = &students[i];
        if (s->rollNo == rollNo) {
            printf("\n--- Student Found ---\n");
            printf("Roll Number : %d\n", s->rollNo);
            printf("Name        : %s\n", s->name);
            printf("Marks       : %.2f, %.2f, %.2f\n", s->marks[0], s->marks[1], s->marks[2]);
            printf("Total Marks : %.2f\n", s->total);
            printf("Average     : %.2f\n", s->average);
            return;
        }
    }
    printf("\nStudent with Roll Number %d not found.\n", rollNo);
}

// 5. Function to save records to a binary file
void saveToFile(const struct Student *students, int count) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
    printf("\n%d record(s) saved to '%s' successfully!\n", count, FILE_NAME);
}

// Function to retrieve records from the binary file
void loadFromFile(struct Student *students, int *count) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        *count = 0;
        return;
    }

    if (fread(count, sizeof(int), 1, fp) != 1 || *count < 0 || *count > MAX_STUDENTS) {
        *count = 0;
        fclose(fp);
        return;
    }

    fread(students, sizeof(struct Student), *count, fp);
    fclose(fp);
    printf("\nLoaded %d record(s) from '%s'.\n", *count, FILE_NAME);
}
