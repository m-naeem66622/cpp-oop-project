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
void managePatientsMenu();

void viewPatientProfile();
void viewDoctorProfile();
void updatePatientProfile();
void updateDoctorProfile();
void viewAssignedPatients();
void loginPatient();
void loginDoctor();
void registerPatient();
void registerDoctor();
void viewMedicalHistory();
void viewAllPatients();
void selectPatient();
bool checkPatientIsNotNull(std::string str);
void assignPatient();
void unassignPatient();
void addMedicalHistory();
void updateMedicalHistory();
void deleteMedicalHistory();

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
        case 4:
            patient = nullptr; // Reset the loggedin user
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
    displayHeader(118);
    std::cout << centerString("======================================================================================================================") << std::endl;
    std::cout << centerString("Medical History") << std::endl;
    std::cout << centerString("======================================================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to view medical history!"))
    {
        return;
    }

    if (patient->getMedicalHistory().empty())
    {
        std::cout << centerString("No medical history found.") << std::endl;
    }
    else
    {
        std::cout << patient->getMedicalHistory();
    }
    std::cout << centerString("======================================================================================================================") << std::endl;
    std::cout << centerString("Press any key to continue...", 119, false) << std::endl;
    getch();
}

void viewAllPatients()
{
    displayHeader(110);
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("All Patients") << std::endl;
    std::cout << centerString("==============================================================================================================") << std::endl;
    if (hospital.getPatients().empty())
    {
        std::cout << centerString("No patients found.") << std::endl;
    }
    else
    {
        std::cout << hospital.getPatients();
    }
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Press any key to continue...", 111, false) << std::endl;
    getch();
}

void selectPatient()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Select Patient") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << hospital.getPatients();
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Enter the ID of the patient you want to select: ", MAX_WIDTH, false);

    int id;
    while (!(std::cin >> id) || hospital.findPatient(id) == nullptr)
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    patient = hospital.findPatient(id);

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Patient selected successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
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
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Doctor Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View All Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Manage Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("6. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-6): ", MAX_LENGTH, false);

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
            viewDoctorProfile();
            break;
        case 2:
            updateDoctorProfile();
            break;
        case 3:
            viewAllPatients();
            break;
        case 4:
            viewAssignedPatients();
            break;
        case 5:
            managePatientsMenu();
            break;
        case 6:
            doctor = nullptr; // Reset the loggedin user
        }

    } while (choice != MAX_CHOICES);
}

void viewDoctorProfile()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Doctor Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << *doctor;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void updateDoctorProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Update Doctor Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("OLD INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *doctor;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("NEW INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    doctor->getInfoFromUser(MAX_LENGTH);
    hospital.writeDoctorsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void viewAssignedPatients()
{
    displayHeader(110);
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Assigned Patients") << std::endl;
    std::cout << centerString("==============================================================================================================") << std::endl;
    if (doctor->getPatientsAssigned().empty())
    {
        std::cout << centerString("No patients assigned.") << std::endl;
    }
    else
    {
        std::cout << doctor->getPatientsAssigned();
    }
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Press any key to continue...", 111, false) << std::endl;
    getch();
}

void managePatientsMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 8;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Patients Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Assign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. Unassign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. View Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Add Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("6. Update Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("7. Remove Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("8. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-8): ", MAX_LENGTH, false);

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
            selectPatient();
            break;
        case 2:
            assignPatient();
            break;
        case 3:
            unassignPatient();
            break;
        case 4:
            viewMedicalHistory();
            break;
        case 5:
            addMedicalHistory();
            break;
        case 6:
            // updateMedicalHistory();
            break;
        case 7:
            // removeMedicalHistory();
            break;
        }

    } while (choice != MAX_CHOICES);
}

bool checkPatientIsNotNull(std::string str)
{
    if (patient == nullptr)
    {
        std::cout << centerString("For this operation, you need to select a patient first.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void assignPatient()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Assign Patient") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to assign patient!"))
    {
        return;
    }

    std::cout << *patient;

    bool _isAssigned = doctor->assignPatient(*patient);
    hospital.writeDoctorsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString(_isAssigned ? "Patient assigned successfully!" : "Patient already assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void unassignPatient()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Unassign Patient") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to unassign patient!"))
    {
        return;
    }

    std::cout << *patient;

    bool _isUnassigned = doctor->unassignPatient(patient->getId());
    hospital.writeDoctorsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString(_isUnassigned ? "Patient unassigned successfully!" : "Patient not assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void addMedicalHistory()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Add Medical History") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to add medical history!"))
    {
        return;
    }

    std::cout << *patient;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    patient->addMedicalHistory();
    hospital.writePatientsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Medical history added successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}
// ----------------------- DOCTOR FUNCTIONS END -----------------------
