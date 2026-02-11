// Attendance Management System
/* This program allows teachers to mark attendance for students and students to view their attendance records.
It uses file handling to store and retrieve attendance data for each student and uses structures to manage user credentials.
Each student has a separate file named "studentX.txt" where X is the roll number.
The program includes a teacher interface for marking and viewing attendance and a student interface for viewing attendance. */

// Login Credentials:
//teacher user ID: teacher
//teacher password: MIT123
//student user ID: student
//student password: MIT456

// Required Libraries
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // added for exit()
#include <ctype.h>   // added for toupper()
#include <time.h>
#include <conio.h> // added for getch()

#define MAX_STUDENTS 100
// Other function prototypes
int file_exists(const char *filename);
void teacherInterface();
void studentInterface();
void mark_attendance();
void view_studentsAttendance();
void student_view_attendance();
void view_all_individual_files();
void view_individual_file();

struct User {
    char user_id[50];
    char password[50];
};

// file_exists implementation
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to get password input with masking
void getPassword(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch(); // read without echoing

        if (ch == 13) { // Enter key 13 is the ASCII code for Enter (\n)
            password[i] = '\0'; // null-terminate the string
            printf("\n");
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // erase last *
            }
        } else if (i < 49) { // limit to 49 chars
            password[i++] = ch;
            printf("*");
        }
    }
}

int main() {
    int ch;
    // Structure for user credentials
    // In a real application, these would be securely stored and managed
    // Here we use hardcoded values for demonstration purposes
    struct User teacher = {"teacher", "MIT123"}; 
    struct User student = {"student", "MIT456"};

    //Main menu loop
    while (1) {
        printf("------------------------------------------------------------\n");
        printf("        Welcome to the Attendance Management System\n");
        printf("------------------------------------------------------------\n");
        printf("1. Login as Teacher\n");
        printf("2. Login as Student\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {

            // Case 1: Teacher Login
            case 1: {
                struct User input;
                int success = 0;

                for (int i = 0; i < 3; i++) {
                    printf("\n--------Model Institute of Technology--------\n");
                    printf("\n===== Teacher Login =====\n");
                    printf("Enter User ID: ");
                    scanf("%s", input.user_id);
                    printf("Enter Password: ");
                    getPassword(input.password); // function to mask password input with asterisks *

                    if (strcmp(input.user_id, teacher.user_id) == 0 &&
                        strcmp(input.password, teacher.password) == 0) {
                        teacherInterface();  // returns to main menu after this
                        success = 1;
                        break;
                    } else {
                        printf("Invalid User ID or Password. Please try again.\n");
                    }
                }

                if (!success) {
                    printf("Too many failed attempts. Returning to main menu...\n");
                }
                break;
            }

            // Case 2: Student Login
            case 2: {
                struct User input;
                int success = 0;
                /* Loop for 3 attempts . This allows the user to try logging in multiple times and if they fail, they will be returned to the main menu */
                for (int i = 0; i < 3; i++) {
                    printf("\n--------Model Institute of Technology--------\n");
                    printf("\n===== Student Login =====\n");
                    printf("Enter User ID: ");
                    scanf("%s", input.user_id);
                    printf("Enter Password: ");
                    getPassword(input.password); // function to mask password input with asterisks *

                    if (strcmp(input.user_id, student.user_id) == 0 &&
                        strcmp(input.password, student.password) == 0) {
                        studentInterface();  // returns to main menu after this
                        success = 1;
                        break;
                    } else {
                        printf("Invalid User ID or Password. Please try again.\n");
                    }
                }

                if (!success) {
                    printf("Too many failed attempts. Returning to main menu...\n");
                }
                break;
            }

            case 3:
                printf("Thank you for using the system. Goodbye!\n");
                exit(0);  // properly end the program
            
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}


void teacherInterface() {
    printf("Welcome to the Teacher Interface!\n");
    int choice;
    while (1) {
        printf("\n--------Model Institute of Technology--------\n");
        printf("\n===== Attendance Management Menu =====\n");
        printf("1. Mark Today's Attendance\n");
        printf("2. View All Student Attendance\n");
        printf("3. Go Back to Main Menue\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: mark_attendance(); break; // Call to mark attendance function
            case 2: view_studentsAttendance(); break; // Call to view students' attendance function
            case 3: return; // Exit the teacher interface and return to main menu
            default: printf("Invalid choice.\n");
        }
    }
}

void studentInterface() {
    int choice;
    while (1) {  // Loop added for continuous use
        printf("\n------------------Student's Portal------------------\n");
        printf("1. View Attendance Details\n");
        printf("2. Go Back to Main Menu\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        switch (choice) {
            case 1: student_view_attendance(); break;
            case 2: return;  // Exit the student interface
            default: printf("Invalid choice.\n");
        }
    }
}

void mark_attendance() {
    char filename[20];      // Stores each student's filename
    char name[50];          // Stores student name
    int roll;               // Stores student roll number
    int present_count, absent_count, late_count;  // Attendance counters
    char status[3];         // Input for attendance status (P, AB, L)

    // Get today’s date in the format YYYY-MM-DD
    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);
    char date_str[20];
    sprintf(date_str, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    printf("\n--- Mark Today's Attendance ---\n");

    // Loop through all students one by one
    for (int i = 1; i <= MAX_STUDENTS; i++) {
        sprintf(filename, "student%d.txt", i);  // Create filename like student1.txt

        // Check if student file exists
        if (!file_exists(filename)) {
            printf("File %s not found. Stopping attendance marking.\n", filename);
            break;
        }

        FILE *fp = fopen(filename, "r");  // Open file to read
        if (!fp) {
            printf("Cannot open %s\n", filename);
            continue;
        }

        // Initialize counts to 0 in case not found
        present_count = 0;
        absent_count = 0;
        late_count = 0;

        // Read name, roll number, and previous attendance counts
        if (fscanf(fp, "Name: %[^\n]\nRoll No: %d\nPresent: %d\nAbsent: %d\nLate: %d\n",
            name, &roll, &present_count, &absent_count, &late_count) != 5) {
            printf("Error reading counters from %s\n", filename);
            fclose(fp);
            continue;
        }

        // Read the rest of the file to keep attendance history
        char history[2000] = "";
        char line[200];
        while (fgets(line, sizeof(line), fp)) {
            strcat(history, line);
        }
        fclose(fp);  // Close file after reading

        // Show student info and ask for today's attendance
        printf("\nRoll: %d | Name: %s\n", roll, name);

        // Keep asking until user gives valid input
        while (1) {
            printf("Enter attendance (P = Present, L = Late, AB = Absent): ");
            scanf("%2s", status);

            // Convert input to uppercase to handle lowercase inputs
            for (int j = 0; status[j]; j++) {
                status[j] = toupper((unsigned char)status[j]);
            }

            if (strcmp(status, "L") == 0) {
                // If Late
                late_count++;
                if (late_count > 3) {
                    // If more than 3 lates, count as Absent
                    printf("More than 3 lates. Marking Absent and resetting lates.\n");
                    strcpy(status, "AB");
                    late_count = 0;
                    absent_count++;
                } else {
                    printf("Marked Late.\n");
                    present_count++;  // Late also counts as present
                }
                break;  // Valid input, break the loop
            } else if (strcmp(status, "P") == 0) {
                // If Present
                present_count++;
                break;  // Valid input
            } else if (strcmp(status, "AB") == 0) {
                // If Absent
                absent_count++;
                break;  // Valid input
            } else {
                // If anything else is typed
                printf("Invalid input. Please try again.\n");
            }
        }

        // Now update the file with new attendance info
        fp = fopen(filename, "w");  // Open file to overwrite
        if (!fp) {
            printf("Cannot write to %s\n", filename);
            continue;
        }

        // Write updated name, roll, and counters
        fprintf(fp, "Name: %s\nRoll No: %d\nPresent: %d\nAbsent: %d\nLate: %d\n",
                name, roll, present_count, absent_count, late_count);

        // Write today's attendance at the top
        fprintf(fp, "Attendance for %s: %s\n", date_str, status);

        // Add back the old history
        fprintf(fp, "%s", history);
        fclose(fp);  // Close file after writing
    }

    printf("\nAttendance marking done.\n");
    printf("Note: If the students are late for more than 3 times, they will be marked as Absent.\n");
    printf("------------------------------------------------------------\n");
}


void view_studentsAttendance() {
    int ch;
    printf("1. View All Attendance Records\n");
    printf("2. View Attendance by Roll Number\n");
    printf("Choose option: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            view_all_individual_files();
            break;
        case 2:
            view_individual_file();
            break;
    }
}

void view_all_individual_files() {
    char filename[20];
    char line[256];
    int found = 0;


    printf("\n--- All Individual Student Files ---\n");
    printf("Note: If the stuents are late for more than 3 times, they will be marked as Absent.\n");

    for (int i = 1; i <= MAX_STUDENTS; i++) { // Loop through all possible student file
        // Construct filename for each student
        sprintf(filename, "student%d.txt", i);
        if (file_exists(filename)) {
            FILE *fp = fopen(filename, "r"); // Open the file for reading
            if (!fp) continue; // If file cannot be opened, skip to next
            printf("------------------------------------------------------------\n");
            // Read and print the contents of the file
            while (fgets(line, sizeof(line), fp)) {
                printf("%s", line);
            }
            fclose(fp); // Close the file after reading
            found = 1; // Set found to true if at least one file is read
        }
    }

    if (!found) {
        printf("No individual student files found.\n");
    }
}
void view_individual_file() {
    int roll;
    char filename[20];
    char line[256];

    printf("Enter Roll Number: ");
    scanf("%d", &roll);
    sprintf(filename, "student%d.txt", roll);

    if (!file_exists(filename)) {
        printf("No record found for Roll Number %d.\n", roll);
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not open file %s\n", filename);
        return;
    }

    printf("\nRecords of %s:\n", filename);
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    printf("\nNote: If the students are late for more than 3 times, they will be marked as Absent.\n");
    fclose(fp);
}



void student_view_attendance() {
    int roll;
    char filename[256];
    char name[50];
    int roll_no;
    int lates = 0, presents = 0, absents = 0;

    printf("Enter your Roll Number to view attendance: ");
    scanf("%d", &roll);
    getchar();  // Clear newline from input buffer

    snprintf(filename, sizeof(filename), "student%d.txt", roll);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Attendance record not found for roll number %d.\n", roll);
        return;
    }

    char line[256];
    printf("\nAttendance History:\n");

    while (!feof(file)) {
    fgets(line, sizeof(line), file);  // read one line from file

    if (feof(file)) break;  // in case fgets reads the last line


    // sscanf reads formatted data from the string 'line' and stores it in variables
    if (sscanf(line, "Name: %[^\n]", name)) continue; // Extract name from line
    if (sscanf(line, "Roll No: %d", &roll_no)) continue; // Extract roll number from line
    // sscanf() extracts the actual name from line and puts it into the name variable.

    if (strncmp(line, "Attendance for", 14) == 0) { // Check if line starts with "Attendance for"
        // Print the attendance line
        printf("%s", line);

        char date[20], status[3];
        if (sscanf(line, "Attendance for %[^:]: %2s", date, status) == 2) {
            if (strcmp(status, "P") == 0) {
                presents++;
            } else if (strcmp(status, "AB") == 0) {
                absents++;
            } else if (strcmp(status, "L") == 0) {
                lates++;
            }
        }
    }

 }
    printf("\n--- Attendance Summary ---\n");
    printf("Name   : %s\n", name);
    printf("Roll No: %d\n", roll_no);
    printf("Present: %d days\n", presents);
    printf("Absent : %d days\n", absents);
    printf("Late   : %d times\n", lates);
    printf("\n----------------------------------------------------------------------------\n");
    printf("Note: If you are late for more than 3 times, you will be marked as Absent.\n");
    printf("----------------------------------------------------------------------------\n");
    // Close the file after reading
    fclose(file);
}
