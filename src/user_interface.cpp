#include "user_interface.h"
#ifdef _WIN32        // if the current operating system is Windows
#include <windows.h> // WriteConsoleW
#endif
#undef max

void UserInterface::wprint(std::wstring str, bool modify, int width, bool center)
{
#ifdef _WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n_written;

    std::wstring strTemp = str;

    if (modify)
    {
        int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
        if (padLen < 0)
        {
            padLen = 0;
        }
        std::wstring padding(padLen, L' ');

        strTemp = padding + str;
    }

    WriteConsoleW(handle, strTemp.c_str(), (DWORD)strTemp.size(), &n_written, NULL);
#else
    std::wcout << message;
#endif
}

void UserInterface::displayHeader(int len = MAX_WIDTH)
{
    system("cls");
    std::cout << Util::centerString(std::string(len, '=')) << std::endl;
    std::cout << std::endl;
    std::cout << Util::centerString("  _    _  ____   _____   _    _            _ _   _        _____           _             ") << std::endl;
    std::cout << Util::centerString(" | |  | |/ __ \\ / ____| | |  | |          | | | | |      / ____|         | |            ") << std::endl;
    ;
    std::cout << Util::centerString(" | |  | | |  | | |  __  | |__| | ___  __ _| | |_| |__   | |     ___ _ __ | |_ ___ _ __  ") << std::endl;
    std::cout << Util::centerString(" | |  | | |  | | | |_ | |  __  |/ _ \\/ _` | | __| '_ \\  | |    / _ \\ '_ \\| __/ _ \\ '__| ") << std::endl;
    ;
    std::cout << Util::centerString(" | |__| | |__| | |__| | | |  | |  __/ (_| | | |_| | | | | |___|  __/ | | | ||  __/ |    ") << std::endl;
    std::cout << Util::centerString("  \\____/ \\____/ \\_____| |_|  |_|\\___|\\__,_|_|\\__|_| |_|  \\_____\\___|_| |_|\\__\\___|_|    ") << std::endl;
    ;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << Util::centerString("Location: Hafiz Hayat Campus, Gujrat, Pakistan") << std::endl;
    std::cout << std::endl;
    // std::cout <<Util::centerString("Developed With +1F90D By:", 30, false) << std::endl;
    wprint(L"Developed With 🤍 By", true);
    std::cout << std::endl;
    std::cout << Util::centerString("-> Muhammad Naeem - 23014119-156", 33, false) << std::endl;
    std::cout << Util::centerString("-> Asyha Shakeel  - 23014119-043", 33, false) << std::endl;
    std::cout << Util::centerString("-> Zoha Azam      - 23014119-071", 33, false) << std::endl;
}

void UserInterface::displayMainMenu()
{
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Main Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. Continue with Patient        ") << std::endl;
        std::cout << Util::centerString("2. Continue with Doctor         ") << std::endl;
        std::cout << Util::centerString("3. Continue with Nurse          ") << std::endl;
        std::cout << Util::centerString("4. Exit                         ") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-4): ");

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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
            std::cout << Util::centerString("Exiting...", MAX_WIDTH) << std::endl;
            break;
        }
    } while (choice != 4);
}

// ----------------------- PATIENT FUNCTIONS START -----------------------
void UserInterface::patientStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Patient Startup Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. Login", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Register", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. Go Back to Main Menu", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-3): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::loginPatient()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Patient Login Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;
    char option = '\0';

    int id;
    std::string password;

    do
    {
        std::cout << Util::centerString("Enter your ID: ", MAX_LENGTH, false);
        while (!(std::cin >> id))
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid id: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << Util::centerString("Enter your password: ", MAX_LENGTH, false);
        std::getline(std::cin, password);

        patient = hospital.authenticatePatient(id, password);

        if (patient != nullptr)
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout <<Util::centerString("Welcome " + patient->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && patient == nullptr);
}

void UserInterface::registerPatient()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Patient Registration Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addPatient(MAX_LENGTH);

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::patientMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Patient Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-4): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::viewPatientProfile()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Patient Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to view profile!"))
        return;

    std::cout << *patient;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::updatePatientProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Update Patient Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("OLD INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *patient;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("NEW INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    patient->getInfoFromUser(MAX_LENGTH);
    hospital.writePatientsData();

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::viewMedicalHistory()
{
    displayHeader(118);
    std::cout << Util::centerString("======================================================================================================================") << std::endl;
    std::cout << Util::centerString("Medical History") << std::endl;
    std::cout << Util::centerString("======================================================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to view medical history!"))
        return;

    if (patient->getMedicalHistory().empty())
    {
        std::cout << Util::centerString("No medical history found.") << std::endl;
    }
    else
    {
        std::cout << patient->getMedicalHistory();
    }
    std::cout << Util::centerString("======================================================================================================================") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 119, false) << std::endl;
    getch();
}

void UserInterface::viewAllPatients()
{
    displayHeader(110);
    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    std::cout << Util::centerString("All Patients") << std::endl;
    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    if (hospital.getPatients().empty())
    {
        std::cout << Util::centerString("No patients found.") << std::endl;
    }
    else
    {
        std::cout << hospital.getPatients();
    }
    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 110, false) << std::endl;
    getch();
}

void UserInterface::selectPatient(char from)
{
    displayHeader(110);
    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    std::cout << Util::centerString("Select Patient") << std::endl;
    std::cout << Util::centerString("==============================================================================================================") << std::endl;

    if (hospital.getPatients().empty())
    {
        std::cout << Util::centerString("No patients found.") << std::endl;
        std::cout << Util::centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Press any key to continue...", 110, false) << std::endl;
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

    std::cout << Util::centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Enter the ID of the patient you want to select: ");

    int id;
    while (!(std::cin >> id) || ((from == 'd' ? hospital.findPatient(id) : doctor->getAssignedPatient(id)) == nullptr))
    {
        std::cout << std::endl
                  << Util::centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    patient = hospital.findPatient(id);

    std::cout << Util::centerString("--------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Patient selected successfully!", 110, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 110, false) << std::endl;
    getch();
}

bool UserInterface::checkPatientIsNotNull(std::string str)
{
    if (patient == nullptr)
    {
        std::cout << Util::centerString("For this operation, you need to select a patient first.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void UserInterface::manageMedicalHistoryMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 7;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Manage Medical History Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Select Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Selected Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Add Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Update Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("6. Delete Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("7. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-7): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::selectMedicalHistory()
{
    displayHeader(118);
    std::cout << Util::centerString("======================================================================================================================") << std::endl;
    std::cout << Util::centerString("Select Medical History") << std::endl;
    std::cout << Util::centerString("======================================================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to select medical history!"))
        return;

    if (patient->getMedicalHistory().empty())
    {
        std::cout << Util::centerString("No medical history found.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return;
    }

    std::cout << patient->getMedicalHistory();
    std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Enter the ID of the medical history you want to select: ");

    int id;
    while (!(std::cin >> id) || patient->getMedicalHistoryById(id) == nullptr)
    {
        std::cout << std::endl
                  << Util::centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    historyPtr = patient->getMedicalHistoryById(id);

    std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Medical history selected successfully!", 119, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 119, false) << std::endl;
    getch();
}

bool UserInterface::checkMedicalHistoryIsNotNull(std::string str)
{
    if (historyPtr == nullptr)
    {
        std::cout << Util::centerString("For this operation, you need to select a medical history first.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void UserInterface::viewSelectedMedicalHistory()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Selected Medical History") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to view medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to view medical history!"))
        return;

    std::cout << *historyPtr;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::addMedicalHistory()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Add Medical History") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to add medical history!"))
        return;

    if (!checkPatientAssigned("Failed to add medical history!"))
        return;

    std::cout << *patient;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;

    patient->addMedicalHistory(doctor->getName());
    hospital.writePatientsData();

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Medical history added successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::updateMedicalHistory()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Update Medical History") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to add medical history!"))
        return;

    if (!checkPatientAssigned("Failed to add medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to update medical history!"))
        return;

    std::cout << Util::centerString("OLD INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *historyPtr;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("NEW INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    patient->updateMedicalHistory(historyPtr->id, doctor->getName());
    hospital.writePatientsData();

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Medical history updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::deleteMedicalHistory()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Delete Medical History") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkPatientIsNotNull("Failed to delete medical history!"))
        return;

    if (!checkPatientAssigned("Failed to delete medical history!"))
        return;

    if (!checkMedicalHistoryIsNotNull("Failed to delete medical history!"))
        return;

    std::cout << Util::centerString("Are you sure you want to delete the selected medical history? (y/n): ");

    char option;
    std::cin >> option;

    if (option == 'y' || option == 'Y')
    {
        patient->removeMedicalHistory(historyPtr->id);
        hospital.writePatientsData();

        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Medical history deleted successfully!", MAX_WIDTH, false) << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
    }
}
// ----------------------- PATIENT FUNCTIONS END -----------------------

// ----------------------- DOCTOR FUNCTIONS START -----------------------
void UserInterface::doctorStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Doctor Startup Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. Login", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Register", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. Go Back to Main Menu", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-3): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::loginDoctor()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Doctor Login Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;
    char option = '\0';

    int id;
    std::string password;

    do
    {
        std::cout << Util::centerString("Enter your ID: ", MAX_LENGTH, false);
        while (!(std::cin >> id))
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid id: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << Util::centerString("Enter your password: ", MAX_LENGTH, false);
        std::getline(std::cin, password);

        doctor = hospital.authenticateDoctor(id, password);

        if (doctor != nullptr)
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout <<Util::centerString("Welcome " + doctor->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && doctor == nullptr);
}

void UserInterface::registerDoctor()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Doctor Registration Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addDoctor(MAX_LENGTH);

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::doctorMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 5;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Doctor Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. Manage Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Manage Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-5): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::viewDoctorProfile()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Doctor Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << *doctor;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::updateDoctorProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Update Doctor Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("OLD INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *doctor;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("NEW INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    doctor->getInfoFromUser(MAX_LENGTH);
    hospital.writeDoctorsData();

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::viewAssignedPatients(char from)
{
    displayHeader(110);
    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    std::cout << Util::centerString("Assigned Patients") << std::endl;
    std::cout << Util::centerString("==============================================================================================================") << std::endl;

    if (from == 'd')
    {
        if (doctor != nullptr)
        {
            if (doctor->getPatientsAssigned().empty())
            {
                std::cout << Util::centerString("No patients assigned.") << std::endl;
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
            std::cout << Util::centerString("No patients assigned.") << std::endl;
        }
        else
        {
            std::cout << nurse->getPatientsAssigned();
        }
    }

    std::cout << Util::centerString("==============================================================================================================") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 111, false) << std::endl;
    getch();
}

void UserInterface::managePatientsMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Manage Patients Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View All Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Manage Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Manage Medical History", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("6. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-6): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::manageAssignedPatientsMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Manage Assigned Patients Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Assign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Unassign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("6. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-6): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

bool UserInterface::checkPatientAssigned(std::string str)
{
    if (doctor->getAssignedPatient(patient->getId()) == nullptr)
    {
        std::cout << Util::centerString("For this operation, you need to assign a patient first.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void UserInterface::assignPatient(char from)
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Assign Patient") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

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

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString(_isAssigned ? "Patient assigned successfully!" : "Patient already assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::unassignPatient(char from)
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Unassign Patient") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

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

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString(_isUnassigned ? "Patient unassigned successfully!" : "Patient not assigned!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}
// ----------------------- DOCTOR FUNCTIONS END -----------------------

// ----------------------- NURSE FUNCTIONS START -----------------------
void UserInterface::nurseStartupMenu()
{
    const unsigned MAX_CHOICES = 3;
    const unsigned MAX_LENGTH = 35;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Nurse Startup Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. Login", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Register", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. Go Back to Main Menu", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-3): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::loginNurse()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Nurse Login Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;
    char option = '\0';

    int id;
    std::string password;

    do
    {
        std::cout << Util::centerString("Enter your ID: ", MAX_LENGTH, false);
        while (!(std::cin >> id))
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid id: ");
            // Clear error flag
            std::cin.clear();
            // Ignore the rest of the current input line up to newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << Util::centerString("Enter your password: ", MAX_LENGTH, false);
        std::getline(std::cin, password);

        nurse = hospital.authenticateNurse(id, password);

        if (nurse != nullptr)
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login successful!", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
            getch();
            break;
            // std::cout <<Util::centerString("Welcome " + nurse->getName(), MAX_LENGTH, false) << std::endl;
        }
        else
        {
            std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
            std::cout << Util::centerString("Login failed. Please try again.", MAX_WIDTH, false) << std::endl;
            std::cout << Util::centerString("Do you want to try again? (y/n): ", MAX_WIDTH, false);
            std::cin >> option;
        }
    } while ((option != 'n' && option != 'N') && nurse == nullptr);
}

void UserInterface::registerNurse()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Nurse Registration Menu") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    const unsigned MAX_LENGTH = 35;

    hospital.addNurse(MAX_LENGTH);

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Registration successful!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::nurseMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 4;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Nurse Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Update Profile", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-4): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

bool UserInterface::checkNurseIsNotNull(std::string str)
{
    if (nurse == nullptr)
    {
        std::cout << Util::centerString("For this operation, you need to select a nurse first.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString(str, MAX_WIDTH, false) << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return false;
    }
    return true;
}

void UserInterface::viewNurseProfile()
{
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Nurse Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;

    if (!checkNurseIsNotNull("Failed to view nurse profile!"))
        return;

    std::cout << *nurse;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::updateNurseProfile()
{
    const unsigned MAX_LENGTH = 35;
    displayHeader();
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("Update Nurse Profile") << std::endl;
    std::cout << Util::centerString("========================================================================================") << std::endl;
    std::cout << Util::centerString("OLD INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << *nurse;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("NEW INFORMATION") << std::endl;
    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;

    std::cin.ignore();
    nurse->getInfoFromUser(MAX_LENGTH);
    hospital.writeNursesData();

    std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Profile updated successfully!", MAX_WIDTH, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
    getch();
}

void UserInterface::manageNursesMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 5;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Manage Nurses Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View All Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Select Nurse", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Selected Nurse", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Manage Assigned Nurses", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-5): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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

void UserInterface::viewAllNurses()
{
    displayHeader(118);
    std::cout << Util::centerString("======================================================================================================================") << std::endl;
    std::cout << Util::centerString("All Nurses") << std::endl;
    std::cout << Util::centerString("======================================================================================================================") << std::endl;

    if (hospital.getNurses().empty())
    {
        std::cout << Util::centerString("No nurses found.") << std::endl;
    }
    else
    {
        std::cout << hospital.getNurses();
    }

    std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 118, false) << std::endl;
    getch();
}

void UserInterface::selectNurse()
{
    displayHeader(118);
    std::cout << Util::centerString("======================================================================================================================") << std::endl;
    std::cout << Util::centerString("Select Nurse") << std::endl;
    std::cout << Util::centerString("======================================================================================================================") << std::endl;

    if (hospital.getNurses().empty())
    {
        std::cout << Util::centerString("No nurses found.") << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Press any key to continue...", MAX_WIDTH, false) << std::endl;
        getch();
        return;
    }

    std::cout << hospital.getNurses();
    std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Enter the ID of the nurse you want to select: ");

    int id;
    while (!(std::cin >> id) || hospital.findNurse(id) == nullptr)
    {
        std::cout << std::endl
                  << Util::centerString("Invalid input. Please enter a valid id: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    nurse = hospital.findNurse(id);

    std::cout << Util::centerString("----------------------------------------------------------------------------------------------------------------------") << std::endl;
    std::cout << Util::centerString("Nurse selected successfully!", 118, false) << std::endl;
    std::cout << Util::centerString("Press any key to continue...", 118, false) << std::endl;
    getch();
}

void UserInterface::manageAssignedNursesMenu()
{
    const unsigned MAX_LENGTH = 35;
    const unsigned MAX_CHOICES = 6;
    int choice;
    do
    {
        displayHeader();
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("Manage Assigned Nurses Menu") << std::endl;
        std::cout << Util::centerString("========================================================================================") << std::endl;
        std::cout << Util::centerString("1. View Assigned Patients", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("2. Select Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("3. View Selected Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("4. Assign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("5. Unassign Patient", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("6. Go Back", MAX_LENGTH, false) << std::endl;
        std::cout << Util::centerString("----------------------------------------------------------------------------------------") << std::endl;
        std::cout << Util::centerString("Please enter your choice (1-6): ", MAX_LENGTH, false);

        while (!(std::cin >> choice) || choice > MAX_CHOICES)
        {
            std::cout << std::endl
                      << Util::centerString("Invalid input. Please enter a valid choice: ");
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