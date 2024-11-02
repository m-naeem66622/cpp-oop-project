#pragma once

#include "doctor.h"
#include "patient.h"
#include "nurse.h"

class Hospital
{
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Nurse> nurses;

    // Read data from the files and store it in the vectors
    void readPatientsData();
    void readDoctorsData();
    void readNursesData();

public:
    std::string name;
    std::string location;

    Hospital();
    Hospital(std::string name, std::string location);

    void addPatient(int MAX_LENGTH);
    std::vector<Patient> getPatients() const;
    Patient *findPatient(int id);
    Patient findAndShowPatient(int id);
    Patient *authenticatePatient(int id, std::string password);
    void writePatientsData();

    void addDoctor(int MAX_LENGTH);
    Doctor *findDoctor(int id);
    Doctor findAndShowDoctor(int id);
    Doctor *authenticateDoctor(int id, std::string password);
    void writeDoctorsData();

    void addNurse(int MAX_LENGTH);
    std::vector<Nurse> getNurses() const;
    Nurse *findNurse(int id);
    Nurse findAndShowNurse(int id);
    Nurse *authenticateNurse(int id, std::string password);
    void writeNursesData();
};