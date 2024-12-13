#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>




#define STUDENTS_FILE "students.txt"
#define COURSES_FILE "courses.txt"
#define PERFORMANCE_FILE "performance.txt"




struct StudentInfo
{
    char ID[20];
    char NID[17];
    char Name[20];
    char ParentsName[20];
    char ParentsPhone[20];
    char ParentsAddress[30];
    char Email[30];
    char Phone[20];
    char DOB[20];
    char Gender[10];
    char PermanentAddress[30];
    char PresentAddress[30];
    char Department[30];
    int  NumberOfCourse;
};
struct AcademicPerformance {
    char StudentID[20];
    char CourseCode[20];
    float Attendance;  // Percentage of classes attended
    float SGPA;        // SGPA for the course
    int CreditHours;   // Credit hours for the course
};








// Array to store academic performance data
struct AcademicPerformance Performances[100];
int TotalPerformances = 0;








struct AnnualFee {
    char StudentID[20];
    float FeeAmount;  // Annual Fee amount
};








// Array to store annual fee data
struct AnnualFee Fees[100];
int TotalFees = 0;








struct CourseInfo
{
    char StudentID[20];
    char Code[10];
    char Name[20];
};








struct StudentInfo Students[100];
struct CourseInfo Courses[500];








char LoggedInStudentID[20] = ""; // Store the logged-in Student ID








// some global variables
int i,j;
int TotalStudents = 0;
int TotalCourse = 0;
char StudentID[10];
FILE *AllStudents;
FILE *AllCourses;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
FILE *ExistingAllCourses;
FILE *TempAllCourses;
// end








bool IsRunning = true;
void Menu();
void AdminPanel();
void StudentPanel();
void AddNewStudent();
void RecordAcademicPerformance();
void UpdateAcademicPerformance();
void ShowAcademicPerformance();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
void ShowAcademicPerformanceByID();
void StudentLogin();
void LogoutStudent();
void RecordAnnualFee();
void ShowAnnualFee();
int  IsAlreadyExists(char GivenLine[30],char InfoType, char StudentID[300]);
void ErrorAndRestart(char *Error[100]);
void DeleteCourseByIndex(int CourseIndex);
void DeleteStudentByIndex(int CourseIndex);
void AboutThisProject();
void GoBackOrExit();
void ExitProject();
void ShowCoursesEnrolled(char StudentID[10]);
void LoginStudent();












int main()
{
    LoadStudents();
    LoadCourses();
    LoadPerformance();


    while (IsRunning)
    {
        Menu();
        int Option;
        scanf("%d", &Option);
        switch (Option)
        {
        case 0: // Exit the Program
            IsRunning = false;
            ExitProject();
            break;
        case 1: // Admin Panel
            AdminPanel();
            break;
        case 2: // Student Panel
            StudentPanel();
            break;




        case 3: // About This Project
            system("cls");
            AboutThisProject();
            GoBackOrExit();
            break;
        default:
            printf("Invalid Choice! Please try again.\n");
            Sleep(1000);
        }
    }
    return 0;
}




void Menu()
{




    system("cls");
    printf("\t=====================================\n\n");
    printf("\t      STUDENT MANAGEMENT SYSTEM\n\n");
    printf("\t=====================================\n\n");
    printf("\tMAIN MENU\n");
    printf("\t=======================\n\n");
    printf("\t[1] Admin Panel\n");
    printf("\t[2] Student Panel\n");
    printf("\t[3] About This Project\n");
    printf("\t[0] Exit the Program\n\n");
    printf("\t=======================\n");
    printf("\tEnter Your Choice: ");
}








void AdminPanel()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("\t=====================================\n");
        printf("\t           ADMIN PANEL\n");
        printf("\t=====================================\n\n");
        printf("\tChoose an Option:\n");
        printf("\t=======================\n\n");
        printf("\t[1] Add a New Student\n");
        printf("\t[2] Edit Student Details\n");
        printf("\t[3] Record Academic Performance\n");
        printf("\t[4] Record Annual Fee\n");
        printf("\t[5] Update Academic Performance\n");
        printf("\t[6] Search a Student by ID\n");
        printf("\t[7] Delete a Student\n");
        printf("\t[8] Delete All Students\n");
        printf("\t[9] Show All Students\n");
        printf("\t[10] Clear Window\n");
        printf("\t[0] Exit to Main Menu\n");
        printf("\t=======================\n");
        printf("\tEnter Your Choice: ");
        scanf("%d", &choice);








        switch (choice)
        {
        case 1:
            system("cls");
            printf("\n\t\t **** Add A New Student ****\n\n");
            AddNewStudent();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t **** Edit Student Details ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s", StudentID);
            int StudentFoundIndex = SearchStudent(StudentID);
            if (StudentFoundIndex >= 0)
            {
                EditStudent(StudentFoundIndex);
            }
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 3:
            system("cls");
            printf("\n\t\t **** Record Academic Performance ****\n\n");
            RecordAcademicPerformance();
            GoBackOrExit();
            break;








        case 4:
            system("cls");
            printf("\n\t\t **** Record Annual Fee ****\n\n");
            RecordAnnualFee();
            GoBackOrExit();
            break;








        case 5:
            system("cls");
            printf("\n\t\t **** Update Academic Performance ****\n\n");
            UpdateAcademicPerformance();
            GoBackOrExit();
            break;
        case 6:
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s", StudentID);
            int IsFound = SearchStudent(StudentID);
            if (IsFound < 0)
            {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        case 7:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s", StudentID);
            int DeleteStudentFoundIndex = SearchStudent(StudentID);
            if (DeleteStudentFoundIndex >= 0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c", &Sure);
                if (Sure == 'Y' || Sure == 'y')
                {
                    DeleteStudent(DeleteStudentFoundIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }
            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }
            break;
        case 8:
            system("cls");
            printf("\n\t\t **** Delete ALL Students ****\n\n");
            char Sure = 'N';
            getchar();
            printf(" Are you sure want to delete all students? (Y/N): ");
            scanf("%c", &Sure);
            if (Sure == 'Y' || Sure == 'y')
            {
                DeleteAllStudents();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        case 9:
            system("cls");
            printf("\n\t\t **** Show All Students ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 10:
            system("cls");
            break;
        case 0:
            printf("\n\tExiting to Main Menu...\n");
            Sleep(1000);
            return; // Exit to Main Menu
        default:
            printf("Invalid Choice! Please try again.\n");
            Sleep(1500);
        }
    }
}
















void StudentPanel() {
    int option;
    int isLoggedIn = 0;  // to track if the student is logged in








    // Show the student panel with login options
    do {
         system("cls");








        if (isLoggedIn) {
            // If logged in, show the options for student details
            printf("\t=====================================\n");
            printf("\t           Student Panel\n");
            printf("\t=====================================\n\n");
            printf(" Welcome, Student ID: %s\n\n", LoggedInStudentID);
            printf(" 1. Show Academic Performance\n");
            printf(" 2. Show Annual Fee\n");
            printf(" 3. Show Courses Enrolled\n");
            printf(" 4. Logout\n");
            printf(" 0. Exit to Main Menu\n");
            printf(" Enter your choice: ");
            scanf("%d", &option);








            switch (option) {
                case 1:
                    system("cls");
                    ShowAcademicPerformanceByID(LoggedInStudentID);
                    break;
                case 2:
                    //ShowAnnualFee(LoggedInStudentID);
                    system("cls");
                    ShowAnnualFee(LoggedInStudentID);
                    break;
                case 3:
                    system("cls");
                    ShowCoursesEnrolled(LoggedInStudentID);
                    break;
                case 4:
                    system("cls");
                    LogoutStudent();
                    isLoggedIn = 0;  // Logout, so student is not logged in anymore
                    break;
                case 0:
                    printf("Exiting to Main Menu...\n");
                    Sleep(1500);  // wait for 1.5 seconds before returning to the main menu
                    return;
                default:
                    printf("\n Invalid option. Please try again.\n");
                    Sleep(1000);
                    break;
            }
        } else {
            // If not logged in, show the login options
            printf("\t=====================================\n");
            printf("\t           Student Panel\n");
            printf("\t=====================================\n\n");
            printf(" 1. Login\n");
            printf(" 0. Exit to Main Menu\n");
            printf(" Enter your choice: ");
            scanf("%d", &option);








            switch (option) {
                case 1:
                    // Call login function
                    system("cls");
                    LoginStudent();
                    if (strlen(LoggedInStudentID) > 0) {
                        isLoggedIn = 1;  // Mark as logged in if login is successful
                    }
                    break;
                case 0:
                    system("cls");
                    printf("Exiting to Main Menu...\n");
                    Sleep(2500);  // wait for 2.5 seconds before returning to the main menu
                    return;
                default:
                    printf("\n Invalid option. Please try again.\n");
                    Sleep(2000);
                    break;
            }
        }
    } while (1);
}




void LoginStudent() {
    char enteredEmail[30], enteredID[10];
    int found = 0;


    // Prompt for email and ID
    printf("Enter your email: ");
    scanf("%s", enteredEmail);
    printf("Enter your Student ID: ");
    scanf("%s", enteredID);


    // Check if the entered email and ID match an existing student
    for (int i = 0; i < TotalStudents; i++) {
        if (strcmp(Students[i].Email, enteredEmail) == 0 && strcmp(Students[i].ID, enteredID) == 0) {
            // If found, log in the student
            strcpy(LoggedInStudentID, Students[i].ID);
            printf("Login successful! Welcome, %s.\n", Students[i].Name);
            found = 1;
            break;
        }
    }


    // Handle invalid login
    if (!found) {
        printf("Invalid login details. Please try again.\n");
        Sleep(1500);  // Delay to prevent immediate retry
    }
}






// Function to handle student logout
void LogoutStudent() {
    printf("You have been logged out successfully.\n");
    memset(LoggedInStudentID, 0, sizeof(LoggedInStudentID));  // Clear the logged-in student ID
}
















void AddNewStudent()
{
    char StudentID[300];
    char Name[300];
    char Phone[300];
    char Email[300];
    char ParentsName[300];
    char ParentsPhone[300];
    char NID[300];
    char PresentAddress[300];
    char DOB[300];
    char Gender[10];
    char PermanentAddress[300];
    char Department[300];
    int NumberOfCourses;
    char CourseCode[300];
    char CourseName[300];
  // Validation for Name
    int IsValidName = 0;
    while (!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s", Name);
        if (strlen(Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else if (strlen(Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }








    // Validation for Student ID
    int IsValidID = 0;
    while (!IsValidID)
    {
        printf(" Enter The ID: ");
        scanf("%s", StudentID);
        if (IsAlreadyExists(StudentID, 'i', StudentID) > 0)
        {
            printf(" Error: This ID is already exists.\n\n");
            IsValidID = 0;
        }
        else if (strlen(StudentID) > 10)
        {
            printf(" Error: ID can not be more than 10 characters.\n\n");
            IsValidID = 0;
        }
        else if (strlen(StudentID) <= 0)
        {
            printf(" Error: ID can not be empty.\n\n");
            IsValidID = 0;
        }
        else
        {
            IsValidID = 1;
        }
    }








     // Validation for Email
    int IsValidEmail = 0;
    while (!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s", Email);
        if (IsAlreadyExists(Email, 'e', StudentID) > 0)
        {
            printf(" Error: This Email is already exists.\n\n");
            IsValidEmail = 0;
        }
        else if (strlen(Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }








     // Validation for Department
    printf(" Enter Department: ");
    scanf(" %[^\n]s", Department);








     // Validation for Date of Birth
    printf(" Enter Date of Birth (DD-MM-YYYY): ");
    scanf("%s", DOB);








     // Validation for Gender
    printf(" Enter Gender (Male/Female/Other): ");
    scanf("%s", Gender);
















    // Validation for Phone
    int IsValidPhone = 0;
    while (!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s", Phone);
        if (IsAlreadyExists(Phone, 'p', StudentID) > 0)
        {
            printf(" Error: This Phone Number already exists.\n\n");
            IsValidPhone = 0;
        }
        else if (strlen(Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }








    // Validation for NID
    printf(" Enter NID Number: ");
    scanf("%s", NID);








    // Validation for Present Address
    printf(" Enter Present Address: ");
    scanf(" %[^\n]s", PresentAddress);
















    // Validation for Permanent Address
    printf(" Enter Permanent Address: ");
    scanf(" %[^\n]s", PermanentAddress);
























 // Validation for Parent's Name
    printf(" Enter Parent's Name: ");
    scanf(" %[^\n]s", ParentsName);








    // Validation for Parent's Phone
    int IsValidParentsPhone = 0;
    while (!IsValidParentsPhone)
    {
        printf(" Enter Parent's Phone: ");
        scanf("%s", ParentsPhone);
        if (strlen(ParentsPhone) > 20)
        {
            printf(" Error: Parent's Phone can not be more than 20 characters.\n\n");
            IsValidParentsPhone = 0;
        }
        else
        {
            IsValidParentsPhone = 1;
        }
    }
  // Validation for Number of Courses
    int IsValidNumberOfCourse = 0;
    while (!IsValidNumberOfCourse)
    {
        printf(" Number of courses: ");
        scanf("%d", &NumberOfCourses);
        if (NumberOfCourses <= 0 || NumberOfCourses > 10)
        {
            printf(" Error: Number of courses can not be more than 10 and less than 1.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }
    // Storing data in structure
    strcpy(Students[TotalStudents].ID, StudentID);
    strcpy(Students[TotalStudents].Name, Name);
    strcpy(Students[TotalStudents].Phone, Phone);
    strcpy(Students[TotalStudents].Email, Email);
    strcpy(Students[TotalStudents].ParentsName, ParentsName);
    strcpy(Students[TotalStudents].ParentsPhone, ParentsPhone);
    strcpy(Students[TotalStudents].NID, NID);
    strcpy(Students[TotalStudents].PresentAddress, PresentAddress);
    strcpy(Students[TotalStudents].DOB, DOB);
    strcpy(Students[TotalStudents].Gender, Gender);
    strcpy(Students[TotalStudents].PermanentAddress, PermanentAddress);
    strcpy(Students[TotalStudents].Department, Department);
    Students[TotalStudents].NumberOfCourse = NumberOfCourses;
    TotalStudents++;








    // Adding courses
    for (int i = 0; i < NumberOfCourses; i++)
    {
        printf(" Enter Course %d Code: ", i + 1);
        scanf("%s", CourseCode);








        printf(" Enter Course %d Name: ", i + 1);
        scanf(" %[^\n]s", CourseName);








        strcpy(Courses[TotalCourse].StudentID, StudentID);
        strcpy(Courses[TotalCourse].Code, CourseCode);
        strcpy(Courses[TotalCourse].Name, CourseName);
        TotalCourse++;
    }


    SaveCourses(); // After adding new courses.
    TotalStudents++;
    SaveStudents(); // Save the updated list to file


    printf("\n Student Added Successfully.\n\n");
}








void RecordAnnualFee() {
    char studentID[10];
    float feeAmount;
    int studentFoundIndex = -1;








    printf("Enter the Student ID to input annual fee: ");
    scanf("%s", studentID);








    // Check if the student exists
    for (int i = 0; i < TotalStudents; i++) {
        if (strcmp(Students[i].ID, studentID) == 0) {
            studentFoundIndex = i;
            break;
        }
    }








    if (studentFoundIndex == -1) {
        printf("Student with ID %s not found!\n", studentID);
        return;
    }








    // Input the annual fee
    printf("Enter the annual fee for Student ID %s: ", studentID);
    scanf("%f", &feeAmount);








    // Store the fee information in the `Fees` array
    strcpy(Fees[TotalFees].StudentID, studentID);
    Fees[TotalFees].FeeAmount = feeAmount;
    TotalFees++;








    printf("Annual fee of %.2f has been successfully recorded for Student ID %s.\n", feeAmount, studentID);
}








void ShowAnnualFee() {
    char studentID[10];
    int studentFound = 0;








    printf("Enter the Student ID to view annual fee: ");
    scanf("%s", studentID);








    // Search for the student and display their fee
    for (int i = 0; i < TotalFees; i++) {
        if (strcmp(Fees[i].StudentID, studentID) == 0) {
            printf("Student ID: %s\n", studentID);
            printf("Annual Fee: %.2f\n", Fees[i].FeeAmount);
            studentFound = 1;
            break;
        }
    }








    if (!studentFound) {
        printf("No annual fee record found for Student ID %s.\n", studentID);
    }
}
















void RecordAcademicPerformance() {
    system("cls");
    char StudentID[10];
    printf("\n Enter the Student ID to record performance: ");
    scanf("%s", StudentID);








    int StudentFoundIndex = SearchStudent(StudentID);
    if (StudentFoundIndex == -1) {
        printf(" Error: Student not found.\n");
        return;
    }








    printf("\n\t Recording Academic Performance for %s\n\n", Students[StudentFoundIndex].Name);
    int NumCourses = Students[StudentFoundIndex].NumberOfCourse;








    float TotalWeightedSGPA = 0;
    int TotalCredits = 0;








    for (int i = 0; i < NumCourses; i++) {
        char CourseCode[20];
        printf(" Enter Course Code (%d/%d): ", i + 1, NumCourses);
        scanf("%s", CourseCode);








        float Attendance, SGPA;
        int CreditHours;








        printf(" Enter Attendance (%%): ");
        scanf("%f", &Attendance);








        printf(" Enter SGPA: ");
        scanf("%f", &SGPA);








        printf(" Enter Credit Hours: ");
        scanf("%d", &CreditHours);








        // Add performance data to array
        strcpy(Performances[TotalPerformances].StudentID, StudentID);
        strcpy(Performances[TotalPerformances].CourseCode, CourseCode);
        Performances[TotalPerformances].Attendance = Attendance;
        Performances[TotalPerformances].SGPA = SGPA;
        Performances[TotalPerformances].CreditHours = CreditHours;
        TotalPerformances++;








        // Calculate weighted SGPA
        TotalWeightedSGPA += SGPA * CreditHours;
        TotalCredits += CreditHours;
    }








    // Calculate overall CGPA
    float CGPA = TotalWeightedSGPA / TotalCredits;
    printf("\n Academic Performance Recorded Successfully!\n");
    printf(" Overall CGPA: %.2f\n", CGPA);
    SavePerformance(); // Save updated performance records.




}
void UpdateAcademicPerformance() {
    system("cls");
    char StudentID[10];
    printf("\n Enter the Student ID to update performance: ");
    scanf("%s", StudentID);








    int StudentFoundIndex = SearchStudent(StudentID);
    if (StudentFoundIndex == -1) {
        printf(" Error: Student not found.\n");
        return;
    }








    printf("\n\t Updating Academic Performance for %s\n\n", Students[StudentFoundIndex].Name);








    char CourseCode[20];
    printf(" Enter the Course Code to update: ");
    scanf("%s", CourseCode);








    int PerformanceIndex = -1;
    for (int i = 0; i < TotalPerformances; i++) {
        if (strcmp(StudentID, Performances[i].StudentID) == 0 &&
            strcmp(CourseCode, Performances[i].CourseCode) == 0) {
            PerformanceIndex = i;
            break;
        }
    }








    if (PerformanceIndex == -1) {
        printf(" Error: Performance data for this course not found.\n");
        return;
    }








    printf("\n Updating details for Course %s:\n", CourseCode);








    float Attendance, SGPA;
    int CreditHours;








    printf(" Enter New Attendance (%%): ");
    scanf("%f", &Attendance);








    printf(" Enter New SGPA: ");
    scanf("%f", &SGPA);








    printf(" Enter New Credit Hours: ");
    scanf("%d", &CreditHours);








    // Update the performance data
    Performances[PerformanceIndex].Attendance = Attendance;
    Performances[PerformanceIndex].SGPA = SGPA;
    Performances[PerformanceIndex].CreditHours = CreditHours;








    printf("\n Academic Performance Updated Successfully!\n");








    // Recalculate CGPA
    float TotalWeightedSGPA = 0;
    int TotalCredits = 0;
    for (int i = 0; i < TotalPerformances; i++) {
        if (strcmp(StudentID, Performances[i].StudentID) == 0) {
            TotalWeightedSGPA += Performances[i].SGPA * Performances[i].CreditHours;
            TotalCredits += Performances[i].CreditHours;
        }
    }








    float CGPA = TotalWeightedSGPA / TotalCredits;
    printf(" Updated Overall CGPA: %.2f\n", CGPA);
    SavePerformance(); // Save updated performance records.




}








void ShowAllStudents()
{
    printf("===========================================================================================\n");
    printf("|                                   STUDENT MANAGEMENT SYSTEM                              |\n");
    printf("|===================================== ALL STUDENTS ======================================|\n");
    printf("===========================================================================================\n");








    for (int i = 0; i < TotalStudents; i++)
    {
        printf("\nStudent %d Information:\n", i + 1);
        printf("---------------------------------------------\n");
        printf(" ID:                %s\n", Students[i].ID);
        printf(" Name:              %s\n", Students[i].Name);
        printf(" Email:             %s\n", Students[i].Email);
        printf(" Phone:             %s\n", Students[i].Phone);
        printf(" Parent's Name:     %s\n", Students[i].ParentsName);
        printf(" Parent's Phone:    %s\n", Students[i].ParentsPhone);
        printf(" NID:               %s\n", Students[i].NID);
        printf(" Present Address:   %s\n", Students[i].PresentAddress);
        printf(" Date of Birth:     %s\n", Students[i].DOB);
        printf(" Gender:            %s\n", Students[i].Gender);
        printf(" Permanent Address: %s\n", Students[i].PermanentAddress);
        printf(" Department:        %s\n", Students[i].Department);
        printf(" Number of Courses: %d\n", Students[i].NumberOfCourse);








        printf("\nCourses:\n");
        int courseCount = 0;
        for (int j = 0; j < TotalCourse; j++)
        {
            if (strcmp(Students[i].ID, Courses[j].StudentID) == 0)
            {
                courseCount++;
                printf("  Course Code: %-10s | Course Name: %-20s\n", Courses[j].Code, Courses[j].Name);
            }
        }








        if (courseCount == 0)
        {
            printf("  No courses found.\n");
        }








        printf("\n---------------------------------------------\n");
        printf("===========================================================================================\n");
    }








    if (TotalStudents == 0)
    {
        printf("\nNo student records available.\n");
    }
    printf("===========================================================================================\n");
}
















int SearchStudent(char StudentID[10])
{
    system("cls");
    int StudentFoundIndex = -1;








    for (int i = 0; i < TotalStudents; i++)
    {
        if (strcmp(StudentID, Students[i].ID) == 0)
        {
            StudentFoundIndex = i;
            printf("\nStudent Found:\n");
            printf("+-----------------------------+\n");
            printf("| ID:               %-8s \n", Students[i].ID);
            printf("| Name:             %-18s \n", Students[i].Name);
            printf("| Email:            %-28s \n", Students[i].Email);
            printf("| Phone:            %-18s \n", Students[i].Phone);
            printf("| Parent's Name:    %-18s \n", Students[i].ParentsName);
            printf("| Parent's Phone:   %-18s \n", Students[i].ParentsPhone);
            printf("| NID:              %-18s \n", Students[i].NID);
            printf("| Present Address:  %-29s \n", Students[i].PresentAddress);
            printf("| Date of Birth:    %-18s \n", Students[i].DOB);
            printf("| Gender:           %-8s \n", Students[i].Gender);
            printf("| Permanent Address:%-29s \n", Students[i].PermanentAddress);
            printf("| Department:       %-14s \n", Students[i].Department);
            printf("+-----------------------------+\n");
            printf("\nCourses Enrolled:\n");








            int courseCount = 0;
            for (int j = 0; j < TotalCourse; j++)
            {
                if (strcmp(StudentID, Courses[j].StudentID) == 0)
                {
                    courseCount++;
                    printf("  Course Code: %-10s\n", Courses[j].Code);
                    printf("  Course Name: %-10s\n", Courses[j].Name);
                }
            }
            if (courseCount == 0)
            {
                printf("  No courses found.\n");
            }
            return StudentFoundIndex;
        }
    }








    printf("No Student Found with ID: %s\n", StudentID);
    return StudentFoundIndex;
}
















void EditStudent(int StudentFoundIndex)
{
    printf("\n\t\t **** Update The New Student ****\n\n");








    char StudentID[300];
    strcpy(StudentID, Students[StudentFoundIndex].ID);








    // New fields for editing
    char NewName[300];
    char NewEmail[300];
    char NewPhone[300];
    char NewParentName[300];
    char NewParentPhone[300];
    char NewNID[300];
    char NewDOB[20];
    char NewGender[10];
    char NewDepartment[50];
    char NewAddress[300];
    int NewNumberOfCourses;








    int OldTotalNumberOfCourse = Students[StudentFoundIndex].NumberOfCourse;








    // Prompt for each field, allowing skip (0 for skip)








    printf(" Enter The New Name (0 to skip): ");
    scanf(" %[^\n]s", NewName);
    if (strcmp(NewName, "0") != 0)
        strcpy(Students[StudentFoundIndex].Name, NewName);








    printf(" Enter The New Email (0 to skip): ");
    scanf(" %[^\n]s", NewEmail);
    if (strcmp(NewEmail, "0") != 0)
        strcpy(Students[StudentFoundIndex].Email, NewEmail);








    printf(" Enter The New Phone (0 to skip): ");
    scanf(" %[^\n]s", NewPhone);
    if (strcmp(NewPhone, "0") != 0)
        strcpy(Students[StudentFoundIndex].Phone, NewPhone);








    printf(" Enter The New Parent's Name (0 to skip): ");
    scanf(" %[^\n]s", NewParentName);
    if (strcmp(NewParentName, "0") != 0)
        strcpy(Students[StudentFoundIndex].ParentsName, NewParentName);








    printf(" Enter The New Parent's Phone (0 to skip): ");
    scanf(" %[^\n]s", NewParentPhone);
    if (strcmp(NewParentPhone, "0") != 0)
        strcpy(Students[StudentFoundIndex].ParentsPhone, NewParentPhone);








    printf(" Enter The New NID (0 to skip): ");
    scanf(" %[^\n]s", NewNID);
    if (strcmp(NewNID, "0") != 0)
        strcpy(Students[StudentFoundIndex].NID, NewNID);








    printf(" Enter The New Date of Birth (0 to skip): ");
    scanf(" %[^\n]s", NewDOB);
    if (strcmp(NewDOB, "0") != 0)
        strcpy(Students[StudentFoundIndex].DOB, NewDOB);








    printf(" Enter The New Gender (0 to skip): ");
    scanf(" %[^\n]s", NewGender);
    if (strcmp(NewGender, "0") != 0)
        strcpy(Students[StudentFoundIndex].Gender, NewGender);








    printf(" Enter The New Department (0 to skip): ");
    scanf(" %[^\n]s", NewDepartment);
    if (strcmp(NewDepartment, "0") != 0)
        strcpy(Students[StudentFoundIndex].Department, NewDepartment);








    printf(" Enter The New Address (0 to skip): ");
    scanf(" %[^\n]s", NewAddress);
    if (strcmp(NewAddress, "0") != 0)
        strcpy(Students[StudentFoundIndex].PresentAddress, NewAddress);








    // Number of courses
    printf(" Enter the Number of New Courses (0 to skip): ");
    scanf("%d", &NewNumberOfCourses);








    if (NewNumberOfCourses != 0) {
        // Delete old courses
        int FirstCourseIndex = -1;
        for (int i = 0; i < TotalCourse; i++) {
            if (strcmp(Courses[i].StudentID, StudentID) == 0) {
                if (FirstCourseIndex == -1)
                    FirstCourseIndex = i;
                DeleteCourseByIndex(i);
                i--; // Adjust index after deletion
            }
        }








        // Add new courses
        for (int i = 0; i < NewNumberOfCourses; i++) {
            char NewCourseCode[300];
            char NewCourseName[300];








            printf(" Enter New Course %d Code: ", i + 1);
            scanf(" %[^\n]s", NewCourseCode);








            printf(" Enter New Course %d Name: ", i + 1);
            scanf(" %[^\n]s", NewCourseName);








            strcpy(Courses[TotalCourse].StudentID, StudentID);
            strcpy(Courses[TotalCourse].Code, NewCourseCode);
            strcpy(Courses[TotalCourse].Name, NewCourseName);
            TotalCourse++;
        }








        Students[StudentFoundIndex].NumberOfCourse = NewNumberOfCourses;
    }








    printf("\n Student Updated Successfully.\n");
}








void DeleteStudent(int StudentIndex)
{
    int d;
    int FirstCourseIndexs;
    struct StudentInfo ThisStudents;
    ThisStudents = Students[StudentIndex];
    for(d=0; d<TotalCourse; d++)
    {
        if(strcmp(ThisStudents.ID,Courses[d].StudentID) == 0)
        {
            FirstCourseIndexs = d;
            break;
        }
    }
    for(d=1; d<=ThisStudents.NumberOfCourse; d++)
    {
        DeleteCourseByIndex(FirstCourseIndexs);
    }
    DeleteStudentByIndex(StudentIndex);
    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}








void DeleteAllStudents()
{
    TotalStudents = 0;
    TotalCourse = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}








void ShowAcademicPerformanceByID()
{
    // Check if a student is logged in
    if (strlen(LoggedInStudentID) == 0) {
        printf("Error: You must log in first to view academic performance!\n");
        return;
    }








    int studentFound = 0;
    printf("\nAcademic Performance for Student ID: %s\n", LoggedInStudentID);








    // Check if academic performance exists for the logged-in student
    printf("---------------------------------------------\n");
    printf("|  Course Code  |  Attendance  |    SGPA    |\n");
    printf("---------------------------------------------\n");








    float totalSGPA = 0.0;
    int totalCredits = 0;








    for (int i = 0; i < TotalPerformances; i++) {
        if (strcmp(Performances[i].StudentID, LoggedInStudentID) == 0) {
            studentFound = 1;
            printf("|  %-12s|  %-12.2f|  %-11.2f|\n",
                   Performances[i].CourseCode,
                   Performances[i].Attendance,
                   Performances[i].SGPA);








            // Calculate weighted SGPA
            totalSGPA += Performances[i].SGPA * Performances[i].CreditHours;
            totalCredits += Performances[i].CreditHours;
        }
    }
    printf("---------------------------------------------\n");








    if (studentFound) {
        // Calculate and display CGPA
        float cgpa = (totalCredits > 0) ? totalSGPA / totalCredits : 0.0;
        printf("Overall CGPA: %.2f\n", cgpa);
    } else {
        printf("No academic performance records found for Student ID: %s\n", LoggedInStudentID);
    }








GoBackOrExit();
}








void ShowAcademicPerformance()
{
    char StudentID[300];
    printf("Enter Student ID to search academic performance: ");
    scanf("%s", StudentID);








    int StudentFoundIndex = -1;








    // Search for student
    for (int i = 0; i < TotalStudents; i++) {
        if (strcmp(StudentID, Students[i].ID) == 0) {
            StudentFoundIndex = i;
            break;
        }
    }








    if (StudentFoundIndex == -1) {
        printf("Error: Student with ID %s not found!\n", StudentID);
        return;
    }








    // Display academic performance
    printf("\nAcademic Performance for Student ID: %s\n", Students[StudentFoundIndex].ID);
    printf("Name: %s\n", Students[StudentFoundIndex].Name);
    printf("---------------------------------------------\n");
    printf("|  Course Code  |  Attendance  |    SGPA    |\n");
    printf("---------------------------------------------\n");








    float totalSGPA = 0.0;
    int totalCredits = 0;








    for (int i = 0; i < TotalCourse; i++) {
        if (strcmp(Courses[i].StudentID, StudentID) == 0) {
            int attendance;
            float sgpa;
            int courseCredits;








            // Prompt for attendance, SGPA, and course credits
            printf("Enter attendance for %s: ", Courses[i].Code);
            scanf("%d", &attendance);








            printf("Enter SGPA for %s: ", Courses[i].Code);
            scanf("%f", &sgpa);








            printf("Enter credits for %s: ", Courses[i].Code);
            scanf("%d", &courseCredits);








            // Display the entered data
            printf("|  %-12s|  %-12d|  %-11.2f|\n", Courses[i].Code, attendance, sgpa);








            // Calculate weighted SGPA
            totalSGPA += sgpa * courseCredits;
            totalCredits += courseCredits;
        }
    }
    printf("---------------------------------------------\n");








    // Calculate CGPA
    float cgpa = (totalCredits > 0) ? totalSGPA / totalCredits : 0.0;
    printf("Overall CGPA: %.2f\n", cgpa);




    GoBackOrExit();




}








void DeleteCourseByIndex(int CourseIndex)
{
    int c;
    for(c=0; c<TotalCourse-1; c++)
    {
        if(c>=CourseIndex)
        {
            Courses[c] = Courses[c+1];
        }
    }
    TotalCourse--;


    SaveCourses(); // Save updated course list after deletion.




}








void DeleteStudentByIndex(int CourseIndex)
{
    int s;
    for(s=0; s<TotalStudents-1; s++)
    {
        if(s>=CourseIndex)
        {
            Students[s] = Students[s+1];
        }
    }
    TotalStudents--;
}
















int IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300])
{
    int EmailExists = 0;
    int PhoneExists = 0;
    int IDExists = 0;
    int ep;








    for(ep=0; ep<TotalStudents; ep++)
    {
        if(strcmp(GivenLine,Students[ep].ID) == 0)
        {
            IDExists++;
        }
        if(strcmp(GivenLine,Students[ep].Email) == 0 && strcmp(StudentID,Students[ep].ID) != 0 )
        {
            EmailExists++;
        }
        if(strcmp(GivenLine,Students[ep].Phone) == 0 && strcmp(StudentID,Students[ep].ID) != 0)
        {
            PhoneExists++;
        }








    }








    if(InfoType == 'i')
    {
        return IDExists;
    }
    else if(InfoType == 'e')
    {
        return EmailExists;
    }
    else if(InfoType == 'p')
    {
        return PhoneExists;
    }
    else
    {
        return 0;
    }
}
















void ShowCoursesEnrolled(char StudentID[10])
{
    printf("\n\t\t **** Courses Enrolled ****\n\n");








    for (int i = 0; i < TotalCourse; i++)
    {
        if (strcmp(Courses[i].StudentID, StudentID) == 0)
        {
            printf(" Course Code: %s, Course Name: %s\n", Courses[i].Code, Courses[i].Name);
        }
    }
}








void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}


void LoadStudents() {
    FILE *file = fopen(STUDENTS_FILE, "r");
    if (!file) return;


    TotalStudents = 0;
    while (fscanf(file, "%s %s %s %s %s %s %s %s %s %s %s %s %d",
                  Students[TotalStudents].ID, Students[TotalStudents].NID,
                  Students[TotalStudents].Name, Students[TotalStudents].ParentsName,
                  Students[TotalStudents].ParentsPhone, Students[TotalStudents].ParentsAddress,
                  Students[TotalStudents].Email, Students[TotalStudents].Phone,
                  Students[TotalStudents].DOB, Students[TotalStudents].Gender,
                  Students[TotalStudents].PermanentAddress, Students[TotalStudents].PresentAddress,
                  &Students[TotalStudents].NumberOfCourse) != EOF) {
        TotalStudents++;
    }
    fclose(file);
}
void SaveStudents() {
    FILE *file = fopen(STUDENTS_FILE, "w");
    if (!file) return;


    for (int i = 0; i < TotalStudents; i++) {
        fprintf(file, "%s %s %s %s %s %s %s %s %s %s %s %s %d\n",
                Students[i].ID, Students[i].NID, Students[i].Name, Students[i].ParentsName,
                Students[i].ParentsPhone, Students[i].ParentsAddress, Students[i].Email,
                Students[i].Phone, Students[i].DOB, Students[i].Gender,
                Students[i].PermanentAddress, Students[i].PresentAddress,
                Students[i].NumberOfCourse);
    }
    fclose(file);
}
void LoadCourses() {
    FILE *file = fopen(COURSES_FILE, "r");
    if (!file) return; // If the file does not exist, skip loading.


    TotalCourse = 0;
    while (fscanf(file, "%s %s %[^\n]",
                  Courses[TotalCourse].StudentID,
                  Courses[TotalCourse].Code,
                  Courses[TotalCourse].Name) != EOF) {
        TotalCourse++;
    }
    fclose(file);
}
void SaveCourses() {
    FILE *file = fopen(COURSES_FILE, "w");
    if (!file) return; // If the file cannot be opened, skip saving.


    for (int i = 0; i < TotalCourse; i++) {
        fprintf(file, "%s %s %s\n",
                Courses[i].StudentID,
                Courses[i].Code,
                Courses[i].Name);
    }
    fclose(file);
}
void LoadPerformance() {
    FILE *file = fopen(PERFORMANCE_FILE, "r");
    if (!file) return; // If the file does not exist, skip loading.


    TotalPerformances = 0;
    while (fscanf(file, "%s %s %f %f %d",
                  Performances[TotalPerformances].StudentID,
                  Performances[TotalPerformances].CourseCode,
                  &Performances[TotalPerformances].Attendance,
                  &Performances[TotalPerformances].SGPA,
                  &Performances[TotalPerformances].CreditHours) != EOF) {
        TotalPerformances++;
    }
    fclose(file);
}
void SavePerformance() {
    FILE *file = fopen(PERFORMANCE_FILE, "w");
    if (!file) return; // If the file cannot be opened, skip saving.


    for (int i = 0; i < TotalPerformances; i++) {
        fprintf(file, "%s %s %.2f %.2f %d\n",
                Performances[i].StudentID,
                Performances[i].CourseCode,
                Performances[i].Attendance,
                Performances[i].SGPA,
                Performances[i].CreditHours);
    }
    fclose(file);
}


void AboutThisProject()
{
    printf("\n\t                                    ---- About This Project ----\n\n");
    printf("\t-------------------------\n");
    printf("\t      StudentPulse\n");
    printf("\t-------------------------\n\n");
    printf(" \tCreated By : \n\n");
    printf(" \tTeam Listro \n\n");
    printf(" \tTeam Memebers of Team Listro are -> \n\n");
    printf(" \tMosammat Samiea Jahan Eva\n\tID: 241-15-182\n");
    printf(" \tKhondoker Omayer Islam Rafi\n\tID-241-15-153\n");
    printf(" \tMD. Al-Amin Hossen\n\tID: 241-15-756\n");
    printf(" \tOmayer Fahad\n\tID: 241-15-056\n\n");
    printf(" \tSubmitted To :\n\n");
    printf(" \tProfessor Syed Akhter Hossain\n\n");
}








void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else
    {
        system("cls");
    }
}








void ExitProject()
{
    system("cls");
    int i;
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    char ThankYou[100]     = "========== Thank You ==========\n";
    char SeeYouSoon[100]   = "========= See You Soon ========\n";
    for(i=0; i<strlen(ThankYou); i++)
    {








        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    printf("\t\t\t\t\t\t");
    for(i=0; i<strlen(SeeYouSoon); i++)
    {
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
}
