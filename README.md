# C-Program-Practicals

This repository contains C programming practical assignments completed as part of the First-Year Engineering coursework.

## Programs Included

### 1. Matrix Multiplication
A C program that takes dimensions and elements for two matrices from the user, validates compatibility, and computes their product.

**Key Concepts Used:**
- **2D Arrays:** Stores the input matrices and the resultant product matrix (up to 10×10).
- **Nested Loops:** Iterates through rows and columns to take input, perform multiplication, and print the final matrix.
- **Conditional Validation:** Checks if columns of the first matrix equal rows of the second (`c1 == r2`) before proceeding.

---

### 2. Student Record & Result Management System
A menu-driven C program that manages student academic records and stores them persistently using binary file handling.

**Key Concepts Used:**
- **Structures (`struct Student`):** Stores roll number, name, marks across 3 subjects, total, and average.
- **Pointers:** Used across functions for modifying records, calculating results, and passing arrays efficiently.
- **Binary File Handling (`fopen`, `fwrite`, `fread`):** Saves and retrieves student records to and from `students.dat`.

**Features:**
1. Add multiple student records (supports up to 50 students).
2. Automatically calculate total and average marks.
3. Display all student records in a formatted table.
4. Search for a specific student by roll number.
5. Save records to a binary file and reload them on startup.
