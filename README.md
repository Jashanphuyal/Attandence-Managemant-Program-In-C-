# Attendance Management System

**Trimester Project – Model Institute of Technology**

This is a **C-based Attendance Management System** designed for managing student attendance efficiently. It provides separate interfaces for teachers and students, with secure login credentials, and stores attendance records using file handling.

---

## Features

1. **Teacher Interface**
   - Login with teacher credentials.
   - Mark daily attendance for students.
   - View all student attendance records.
   - View individual student attendance records.
   - Automatically converts more than 3 lates into an absent mark.

2. **Student Interface**
   - Login with student credentials.
   - View personal attendance history.
   - See a summary of presents, absents, and lates.

3. **File Handling**
   - Each student has a separate file (`studentX.txt`) where X is the roll number.
   - Attendance data, including dates and status, is stored in the file.

---

## Login Credentials

- **Teacher**
  - User ID: `teacher`
  - Password: `MIT123`
- **Student**
  - User ID: `student`
  - Password: `MIT456`

---

## How to Run

1. Clone or download the repository.
2. Compile the program using a C compiler:
   ```bash
   gcc attendance_management.c -o attendance_management
