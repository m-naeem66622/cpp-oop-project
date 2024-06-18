#include <iostream>
#include <limits>
#include <conio.h>
#include "hospital.h"
// #include <Windows.h>

#define CONSOLE_WIDTH 148
#define MAX_WIDTH 89

std::string centerString(const std::string &str, int width = CONSOLE_WIDTH, bool center = true);

// NOTE: These functions are major focused on the UI/UX of the application
// not on the actual functionality of the application
// Actual functionality is implemented in the Classes
void displayHeader(int len);
void displayMainMenu();
void patientStartupMenu();
void doctorStartupMenu();
void patientMenu();
void doctorMenu();

void viewPatientProfile();
void updatePatientProfile();
void viewMedicalHistory();
void loginPatient();
void loginDoctor();
void registerPatient();
void registerDoctor();

// typedef struct {
//     int rows, cols;
// } winsz_t;

// winsz_t *get_console_sz (winsz_t *wsz)
// {
//     CONSOLE_SCREEN_BUFFER_INFO csbi;

//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

//     wsz->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//     wsz->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

//     return wsz;
// }
Hospital hospital;

// To hold the loggedin user as pointer
Patient *patient = nullptr;
Doctor *doctor = nullptr;
Nurse *nurse = nullptr;

// 1. Acceccsors
// 2. Full paramterized constructors
// 3. Read and Write function

int main()
{

    // winsz_t wsz;
    // get_console_sz(&wsz);
    // std::cout << "Rows: " << wsz.rows << " Cols: " << wsz.cols << std::endl;

    int choice;

    displayMainMenu();

    return 0;
}

std::string centerString(const std::string &str, int width, bool center)
{
    int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
    if (padLen < 0)
    {
        padLen = 0;
    }
    std::string padding(padLen, ' ');
    return padding + str;
}

void displayHeader(int len = MAX_WIDTH)
{
    system("cls");
    std::cout << centerString(std::string(len, '=')) << std::endl;
    std::cout << std::endl;
    std::cout << centerString("  _    _  ____   _____   _    _            _ _   _        _____           _             ") << std::endl;
    std::cout << centerString(" | |  | |/ __ \\ / ____| | |  | |          | | | | |      / ____|         | |            ") << std::endl;
    ;
    std::cout << centerString(" | |  | | |  | | |  __  | |__| | ___  __ _| | |_| |__   | |     ___ _ __ | |_ ___ _ __  ") << std::endl;
    std::cout << centerString(" | |  | | |  | | | |_ | |  __  |/ _ \\/ _` | | __| '_ \\  | |    / _ \\ '_ \\| __/ _ \\ '__| ") << std::endl;
    ;
    std::cout << centerString(" | |__| | |__| | |__| | | |  | |  __/ (_| | | |_| | | | | |___|  __/ | | | ||  __/ |    ") << std::endl;
    std::cout << centerString("  \\____/ \\____/ \\_____| |_|  |_|\\___|\\__,_|_|\\__|_| |_|  \\_____\\___|_| |_|\\__\\___|_|    ") << std::endl;
    ;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << centerString("Location: Hafiz Hayat Campus, Gujrat, Pakistan");
    std::cout << std::endl;
}

void displayMainMenu()
{
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Main Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. Continue with Patient        ") << std::endl;
        std::cout << centerString("2. Continue with Doctor         ") << std::endl;
        std::cout << centerString("3. Continue with Nurse          ") << std::endl;
        std::cout << centerString("4. Exit                         ") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-4): ");

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid choice: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            patientStartupMenu();
            break;
        case 2:
            doctorStartupMenu();
            break;
        case 3:
            // nurseStartupMenu();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        }
    } while (choice != 4);
}

// ----------------------- PATIENT FUNCTIONS START -----------------------
void patientStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Patient Startup Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. Login", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Register", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. Go Back to Main Menu", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-3): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid choice: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            loginPatient();
            if (patient != nullptr)
            {
                patientMenu();
            }
            break;
        case 2:
            registerPatient();
            loginPatient();
            if (patient != nullptr)
            {
                patientMenu();
            }
            break;
        case 3:
            patient = nullptr; // Reset the loggedin user
            break;
        }
    } while (choice != MAX_CHOICES);
}

void loginPatient()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Patient Login Menu") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;
    char option = '\0';

    int id;
    std::string password;

    do
    {
        std::cout << centerString("Enter your ID: ", MAX_LENGTH, false);
        while (!(std::cin >> id))
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid id: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << centerString("Enter your password: ", MAX_LENGTH, false);
        std::getline(std::cin, password);

        patient = hospital.authenticatePatient(id, password);

        if (patient != nullptr)
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout << centerString("Welcome " + patient->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && patient == nullptr);
}

void registerPatient()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Patient Registration Menu") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addPatient(MAX_LENGTH);

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void patientMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Patient Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-4): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid choice: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            viewPatientProfile();
            break;
        case 2:
            updatePatientProfile();
            break;
        case 3:
            viewMedicalHistory();
            break;
        }

    } while (choice != MAX_CHOICES);
}

void viewPatientProfile()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Patient Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << *patient;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void updatePatientProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Update Patient Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("OLD INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *patient;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("NEW INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    patient->getInfoFromUser(MAX_LENGTH);
    hospital.writePatientsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void viewMedicalHistory()
{
    displayHeader(110);
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Medical History") << std::endl;
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << patient->getMedicalHistory();
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Press any key to continue...", 111, false) << std::endl;
    getch();
}
// ----------------------- PATIENT FUNCTIONS END -----------------------

// ----------------------- DOCTOR FUNCTIONS START -----------------------
void doctorStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Doctor Startup Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. Login", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Register", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. Go Back to Main Menu", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-3): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid choice: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            loginDoctor();
            if (doctor != nullptr)
            {
                doctorMenu();
            }
            break;
        case 2:
            registerDoctor();
            loginDoctor();
            if (doctor != nullptr)
            {
                doctorMenu();
            }
            break;
        case 3:
            doctor = nullptr; // Reset the loggedin user
            break;
        }
    } while (choice != MAX_CHOICES);
}

void loginDoctor()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Doctor Login Menu") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;
    char option = '\0';

    int id;
    std::string password;

    do
    {
        std::cout << centerString("Enter your ID: ", MAX_LENGTH, false);
        while (!(std::cin >> id))
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid id: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << centerString("Enter your password: ", MAX_LENGTH, false);
        std::getline(std::cin, password);

        doctor = hospital.authenticateDoctor(id, password);

        if (doctor != nullptr)
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout << centerString("Welcome " + doctor->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && doctor == nullptr);
}

void registerDoctor()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Doctor Registration Menu") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addDoctor(MAX_LENGTH);

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void doctorMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Doctor Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Appointments", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-4): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << centerString("Invalid input. Please enter a valid choice: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            // viewDoctorProfile();
            break;
        case 2:
            // updateDoctorProfile();
            break;
        case 3:
            // viewAppointments();
            break;
        }

    } while (choice != MAX_CHOICES);
}
// ----------------------- DOCTOR FUNCTIONS END -----------------------
