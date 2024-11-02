#pragma once

#include <limits>
#include <conio.h>
#include "hospital.h"

#define MAX_WIDTH 89

class UserInterface
{
private:
    Hospital hospital;

    // To hold the crendentails or loggedin state of user as pointer
    Patient *patient = nullptr;
    Doctor *doctor = nullptr;
    Nurse *nurse = nullptr;

    MedicalHistory *historyPtr = nullptr;

public:
    // NOTE: These functions are major focused on the UI/UX of the application
    // not on the actual functionality of the application
    // Actual functionality is implemented in the Classes

    void wprint(std::wstring str, bool modify = false, int width = CONSOLE_WIDTH, bool center = true);

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
};