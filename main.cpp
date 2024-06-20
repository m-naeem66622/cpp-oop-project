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
void nurseStartupMenu();
void patientMenu();
void doctorMenu();
void nurseMenu();
void managePatientsMenu();
void manageAssignedPatientsMenu();
void manageMedicalHistoryMenu();
void manageNursesMenu();
void manageAssignedNursesMenu();

void viewPatientProfile();
void viewDoctorProfile();
void viewNurseProfile();
void updatePatientProfile();
void updateDoctorProfile();
void updateNurseProfile();
void viewAssignedPatients(char from = 'd');
void loginPatient();
void loginDoctor();
void loginNurse();
void registerPatient();
void registerDoctor();
void registerNurse();
void viewAllPatients();
void selectPatient(char from = 'd');
void viewMedicalHistory();
bool checkPatientAssigned(std::string str);
bool checkPatientIsNotNull(std::string str);
void assignPatient(char from = 'n');
void unassignPatient(char from = 'n');
void selectMedicalHistory();
bool checkMedicalHistoryIsNotNull(std::string str);
void viewSelectedMedicalHistory();
void addMedicalHistory();
void updateMedicalHistory();
void deleteMedicalHistory();
void viewAllNurses();
void selectNurse();
bool checkNurseIsNotNull(std::string str);

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

// To hold the crendentails or loggedin state of user as pointer
Patient *patient = nullptr;
Doctor *doctor = nullptr;
Nurse *nurse = nullptr;

MedicalHistory *historyPtr = nullptr;

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
            nurseStartupMenu();
            break;
        case 4:
            std::cout << centerString("Exiting...", MAX_WIDTH) << std::endl;
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

    if (!checkPatientIsNotNull("Failed to view profile!"))
        return;

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
        return;

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
    std::cout << centerString("Press any key to continue...", 110, false) << std::endl;
    getch();
}

void selectPatient(char from)
{
    displayHeader(110);
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Select Patient") << std::endl;
    std::cout << centerString("==============================================================================================================") << std::endl;

    if (hospital.getPatients().empty())
    {
        std::cout << centerString("No patients found.") << std::endl;
        std::cout << centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Press any key to continue...", 110, false) << std::endl;
        getch();
        return;
    }

    if (from == 'd')
    {
        std::cout << hospital.getPatients();
    }
    else if (from == 'n')
    {
        std::cout << doctor->getPatientsAssigned();
    }

    std::cout << centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Enter the ID of the patient you want to select: ");

    int id;
    while (!(std::cin >> id) || ((from == 'd' ? hospital.findPatient(id) : doctor->getAssignedPatient(id)) == nullptr))
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    patient = hospital.findPatient(id);

    std::cout << centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Patient selected successfully!", 110, false) << std::endl;
    std::cout << centerString("Press any key to continue...", 110, false) << std::endl;
    getch();
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

void manageMedicalHistoryMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 7;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Medical History Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Select Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Selected Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Add Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Update Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("6. Delete Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("7. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-7): ", MAX_LENGTH, false);

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
            viewMedicalHistory();
            break;
        case 2:
            selectMedicalHistory();
            break;
        case 3:
            viewSelectedMedicalHistory();
            break;
        case 4:
            addMedicalHistory();
            break;
        case 5:
            updateMedicalHistory();
            break;
        case 6:
            deleteMedicalHistory();
            break;
        case 7:
            historyPtr = nullptr; // Reset the selected history
        }

    } while (choice != MAX_CHOICES);
}

void selectMedicalHistory()
{
    displayHeader(118);
    std::cout << centerString("======================================================================================================================") << std::endl;
    std::cout << centerString("Select Medical History") << std::endl;
    std::cout << centerString("======================================================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to select medical history!"))
        return;

    if (patient->getMedicalHistory().empty())
    {
        std::cout << centerString("No medical history found.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return;
    }

    std::cout << patient->getMedicalHistory();
    std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Enter the ID of the medical history you want to select: ");

    int id;
    while (!(std::cin >> id) || patient->getMedicalHistoryById(id) == nullptr)
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    historyPtr = patient->getMedicalHistoryById(id);

    std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Medical history selected successfully!", 119, false) << std::endl;
    std::cout << centerString("Press any key to continue...", 119, false) << std::endl;
    getch();
}

bool checkMedicalHistoryIsNotNull(std::string str)
{
    if (historyPtr == nullptr)
    {
        std::cout << centerString("For this operation, you need to select a medical history first.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void viewSelectedMedicalHistory()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Selected Medical History") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to view medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to view medical history!"))
        return;

    std::cout << *historyPtr;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
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
        return;

    if (!checkPatientAssigned("Failed to add medical history!"))
        return;

    std::cout << *patient;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    patient->addMedicalHistory(doctor->getName());
    hospital.writePatientsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Medical history added successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void updateMedicalHistory()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Update Medical History") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to add medical history!"))
        return;

    if (!checkPatientAssigned("Failed to add medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to update medical history!"))
        return;

    std::cout << centerString("OLD INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *historyPtr;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("NEW INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    patient->updateMedicalHistory(historyPtr->id, doctor->getName());
    hospital.writePatientsData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Medical history updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void deleteMedicalHistory()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Delete Medical History") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to delete medical history!"))
        return;

    if (!checkPatientAssigned("Failed to delete medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to delete medical history!"))
        return;

    std::cout << centerString("Are you sure you want to delete the selected medical history? (y/n): ");

    char option;
    std::cin >> option;

    if (option == 'y' || option == 'Y')
    {
        patient->removeMedicalHistory(historyPtr->id);
        hospital.writePatientsData();

        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Medical history deleted successfully!", MAX_WIDTH, false) << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
    }
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
    const unsigned MAX_CHOICES = 5;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Doctor Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. Manage Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Manage Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-5): ", MAX_LENGTH, false);

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
            managePatientsMenu();
            break;
        case 4:
            manageNursesMenu();
            break;
        case 5:
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

void viewAssignedPatients(char from)
{
    displayHeader(110);
    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Assigned Patients") << std::endl;
    std::cout << centerString("==============================================================================================================") << std::endl;

    if (from == 'd')
    {
        if (doctor != nullptr)
        {
            if (doctor->getPatientsAssigned().empty())
            {
                std::cout << centerString("No patients assigned.") << std::endl;
            }
            else
            {
                std::cout << doctor->getPatientsAssigned();
            }
        }
    }
    else if (from == 'n')
    {
        if (!checkNurseIsNotNull("Failed to view assigned patients!"))
            return;

        if (nurse->getPatientsAssigned().empty())
        {
            std::cout << centerString("No patients assigned.") << std::endl;
        }
        else
        {
            std::cout << nurse->getPatientsAssigned();
        }
    }

    std::cout << centerString("==============================================================================================================") << std::endl;
    std::cout << centerString("Press any key to continue...", 111, false) << std::endl;
    getch();
}

void managePatientsMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Patients Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View All Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Manage Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Manage Medical History", MAX_LENGTH, false) << std::endl;
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
            viewAllPatients();
            break;
        case 2:
            selectPatient();
            break;
        case 3:
            viewPatientProfile();
            break;
        case 4:
            manageAssignedPatientsMenu();
            break;
        case 5:
            manageMedicalHistoryMenu();
            break;
        case 6:
            patient = nullptr; // Reset the selected patient
        }

    } while (choice != MAX_CHOICES);
}

void manageAssignedPatientsMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Assigned Patients Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Assign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Unassign Patient", MAX_LENGTH, false) << std::endl;
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
            viewAssignedPatients();
            break;
        case 2:
            selectPatient();
            break;
        case 3:
            viewPatientProfile();
            break;
        case 4:
            assignPatient();
            break;
        case 5:
            unassignPatient();
            break;
        }

    } while (choice != MAX_CHOICES);
}

bool checkPatientAssigned(std::string str)
{
    if (doctor->getAssignedPatient(patient->getId()) == nullptr)
    {
        std::cout << centerString("For this operation, you need to assign a patient first.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void assignPatient(char from)
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Assign Patient") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to assign patient!"))
        return;

    if (from == 'n' && !checkNurseIsNotNull("Failed to assign patient!"))
        return;

    std::cout << *patient;

    bool _isAssigned = false;
    if (from == 'd')
    {
        _isAssigned = doctor->assignPatient(*patient);
        hospital.writeDoctorsData();
    }
    else if (from == 'n')
    {
        _isAssigned = nurse->assignPatient(*patient);
        hospital.writeNursesData();
    }

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString(_isAssigned ? "Patient assigned successfully!" : "Patient already assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void unassignPatient(char from)
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Unassign Patient") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to unassign patient!"))
        return;

    if (from == 'n' && !checkNurseIsNotNull("Failed to unassign patient!"))
        return;

    std::cout << *patient;

    // bool _isUnassigned = doctor->unassignPatient(patient->getId());
    // hospital.writeDoctorsData();

    bool _isUnassigned = false;
    if (from == 'd')
    {
        _isUnassigned = doctor->unassignPatient(patient->getId());
        hospital.writeDoctorsData();
    }
    else if (from == 'n')
    {
        _isUnassigned = nurse->unassignPatient(patient->getId());
        hospital.writeNursesData();
    }

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString(_isUnassigned ? "Patient unassigned successfully!" : "Patient not assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}
// ----------------------- DOCTOR FUNCTIONS END -----------------------

// ----------------------- NURSE FUNCTIONS START -----------------------
void nurseStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Nurse Startup Menu") << std::endl;
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
            loginNurse();
            if (nurse != nullptr)
            {
                nurseMenu();
            }
            break;
        case 2:
            registerNurse();
            loginNurse();
            if (nurse != nullptr)
            {
                nurseMenu();
            }
            break;
        case 3:
            nurse = nullptr; // Reset the loggedin user
            break;
        }
    } while (choice != MAX_CHOICES);
}

void loginNurse()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Nurse Login Menu") << std::endl;
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

        nurse = hospital.authenticateNurse(id, password);

        if (nurse != nullptr)
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout << centerString("Welcome " + nurse->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && nurse == nullptr);
}

void registerNurse()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Nurse Registration Menu") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addNurse(MAX_LENGTH);

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void nurseMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Nurse Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Assigned Patients", MAX_LENGTH, false) << std::endl;
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
            viewNurseProfile();
            break;
        case 2:
            updateNurseProfile();
            break;
        case 3:
            viewAssignedPatients('n');
            break;
        case 4:
            nurse = nullptr; // Reset the loggedin user
        }

    } while (choice != MAX_CHOICES);
}

bool checkNurseIsNotNull(std::string str)
{
    if (nurse == nullptr)
    {
        std::cout << centerString("For this operation, you need to select a nurse first.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void viewNurseProfile()
{
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Nurse Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;

    if (!checkNurseIsNotNull("Failed to view nurse profile!"))
        return;

    std::cout << *nurse;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void updateNurseProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("Update Nurse Profile") << std::endl;
    std::cout << centerString("========================================================================================") << std::endl;
    std::cout << centerString("OLD INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *nurse;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("NEW INFORMATION") << std::endl;
    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    nurse->getInfoFromUser(MAX_LENGTH);
    hospital.writeNursesData();

    std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void manageNursesMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 5;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Nurses Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View All Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Select Nurse", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Selected Nurse", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Manage Assigned Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Please enter your choice (1-5): ", MAX_LENGTH, false);

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
            viewAllNurses();
            break;
        case 2:
            selectNurse();
            break;
        case 3:
            viewNurseProfile();
            break;
        case 4:
            manageAssignedNursesMenu();
            break;
        case 5:
            nurse = nullptr; // Reset the selected nurse
        }

    } while (choice != MAX_CHOICES);
}

void viewAllNurses()
{
    displayHeader(118);
    std::cout << centerString("======================================================================================================================") << std::endl;
    std::cout << centerString("All Nurses") << std::endl;
    std::cout << centerString("======================================================================================================================") << std::endl;

    if (hospital.getNurses().empty())
    {
        std::cout << centerString("No nurses found.") << std::endl;
    }
    else
    {
        std::cout << hospital.getNurses();
    }

    std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Press any key to continue...", 118, false) << std::endl;
    getch();
}

void selectNurse()
{
    displayHeader(118);
    std::cout << centerString("======================================================================================================================") << std::endl;
    std::cout << centerString("Select Nurse") << std::endl;
    std::cout << centerString("======================================================================================================================") << std::endl;

    if (hospital.getNurses().empty())
    {
        std::cout << centerString("No nurses found.") << std::endl;
        std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return;
    }

    std::cout << hospital.getNurses();
    std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Enter the ID of the nurse you want to select: ");

    int id;
    while (!(std::cin >> id) || hospital.findNurse(id) == nullptr)
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    nurse = hospital.findNurse(id);

    std::cout << centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << centerString("Nurse selected successfully!", 118, false) << std::endl;
    std::cout << centerString("Press any key to continue...", 118, false) << std::endl;
    getch();
}

void manageAssignedNursesMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("Manage Assigned Nurses Menu") << std::endl;
        std::cout << centerString("========================================================================================") << std::endl;
        std::cout << centerString("1. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("4. Assign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << centerString("5. Unassign Patient", MAX_LENGTH, false) << std::endl;
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
            viewAssignedPatients('n');
            break;
        case 2:
            selectPatient('n');
            break;
        case 3:
            viewPatientProfile();
            break;
        case 4:
            assignPatient('n');
            break;
        case 5:
            unassignPatient('n');
            break;
        }

    } while (choice != MAX_CHOICES);
}
// ----------------------- NURSE FUNCTIONS END -----------------------