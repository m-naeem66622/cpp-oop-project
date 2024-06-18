#include "hospital.h"
#include <fstream>
#include <sstream>

Hospital::Hospital()
{
    this->name = "UOG Health Center";
    this->location = "University Of Gujrat, Hafiz Hayat Campus, Gujrat, Pakistan";
    readPatientsData();
}

Hospital::Hospital(std::string name, std::string location)
{
    this->name = name;
    this->location = location;
    readPatientsData();
}

// Read data from patients.csv and medical_histories.csv files
void Hospital::readPatientsData()
{
    std::ifstream patientsFile("patients.csv");
    std::ifstream medicalHistoriesFile("medical_histories.csv");

    if (patientsFile.is_open() && medicalHistoriesFile.is_open())
    {
        std::string line;
        std::getline(patientsFile, line);         // Skip the first line (as it contains the column names)
        std::getline(medicalHistoriesFile, line); // Skip the first line (as it contains the column names)

        while (std::getline(patientsFile, line))
        {
            std::stringstream ss(line);
            std::string id, name, age, address, phoneNumber, bloodGroup, password;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, age, ',');
            std::getline(ss, address, ',');
            std::getline(ss, phoneNumber, ',');
            std::getline(ss, bloodGroup, ',');
            std::getline(ss, password, ',');

            Patient patient(std::stoi(id), name, std::stoi(age), address, phoneNumber, password, bloodGroup);

            std::string medicalHistoryLine;
            while (std::getline(medicalHistoriesFile, medicalHistoryLine))
            {
                std::stringstream medicalHistorySS(medicalHistoryLine);
                std::string historyId, patientId, currentMedications, allergies, doctorAssigned, roomNumber, createdAt, lastUpdatedAt;
                std::getline(medicalHistorySS, historyId, ',');
                std::getline(medicalHistorySS, patientId, ',');
                std::getline(medicalHistorySS, currentMedications, ',');
                std::getline(medicalHistorySS, allergies, ',');
                std::getline(medicalHistorySS, doctorAssigned, ',');
                std::getline(medicalHistorySS, roomNumber, ',');
                std::getline(medicalHistorySS, createdAt, ',');
                std::getline(medicalHistorySS, lastUpdatedAt, ',');

                if (std::stoi(patientId) == patient.getId())
                {
                    Date createdDate(createdAt);
                    Date lastUpdatedDate(lastUpdatedAt);
                    // MedicalHistory history(std::stoi(historyId), currentMedications, allergies, doctorAssigned, roomNumber, createdDate, lastUpdatedDate);
                    // patient.addMedicalHistory(history);
                    patient.addMedicalHistory(std::stoi(historyId), currentMedications, allergies, doctorAssigned, roomNumber, createdDate, lastUpdatedDate);
                }
            }

            this->patients.push_back(patient);
        }

        patientsFile.close();
        medicalHistoriesFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open the file." << std::endl;
    }
}

// -------------------------------- PATIENT FUNCTIONS START --------------------------------
void Hospital::addPatient(int MAX_LENGTH)
{
    int id = 1;
    if (!this->patients.empty())
        id = this->patients.back().getId() + 1;
    std::cout << centerString("Patient ID: ", MAX_LENGTH, false) << id << std::endl;

    std::string password;
    std::cin.ignore();
    std::cout << centerString("Enter the password: ", MAX_LENGTH, false);
    std::getline(std::cin, password);

    Patient patient(id, password);
    patient.getInfoFromUser(MAX_LENGTH);
    this->patients.push_back(patient);

    writePatientsData();
}

Patient *Hospital::findPatient(int id)
{
    for (auto &patient : this->patients)
    {
        if (patient.getId() == id)
        {
            return &patient;
        }
    }
    return nullptr;
}

Patient Hospital::findAndShowPatient(int id)
{
    const Patient *patient = findPatient(id);
    if (patient != nullptr)
    {
        std::cout << *patient << std::endl;
    }
    else
    {
        std::cout << "Patient not found!" << std::endl;
    }
    return *patient;
}

Patient *Hospital::authenticatePatient(int id, std::string password)
{
    Patient *patient = findPatient(id);
    if (patient != nullptr && patient->authenticate(password))
    {
        return patient;
    }
    return nullptr;
}

// Write a CSV file of patients. basic info and medical history in seprate two files
void Hospital::writePatientsData()
{
    std::ofstream patientsFile("patients.csv");
    std::ofstream medicalHistoriesFile("medical_histories.csv");

    if (patientsFile.is_open() && medicalHistoriesFile.is_open())
    {
        patientsFile << "ID,Name,Age,Address,Phone Number,Blood Group,Password\n";
        medicalHistoriesFile << "ID,Patient ID,Current Medications,Allergies,Doctor Assigned,Room Number,Date Created,Last Updated\n";

        for (const auto &patient : this->patients)
        {
            patientsFile << patient.getId() << "," << patient.getName() << "," << patient.getAge() << "," << patient.getAddress() << "," << patient.getPhoneNumber() << "," << patient.getBloodGroup() << patient.getPassword() << "\n";

            for (const auto &history : patient.getMedicalHistory())
            {
                medicalHistoriesFile << history.id << "," << patient.getId() << "," << history.currentMedications << "," << history.allergies << "," << history.doctorAssigned << "," << history.roomNumber << "," << history.createdAt << "," << history.lastUpdatedAt << "\n";
            }
        }

        patientsFile.close();
        medicalHistoriesFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open the file." << std::endl;
    }
}
// -------------------------------- PATIENT FUNCTIONS END --------------------------------

// -------------------------------- DOCTOR FUNCTIONS START --------------------------------
void Hospital::addDoctor(int MAX_LENGTH)
{
    int id = 1;
    if (!this->doctors.empty())
        id = this->doctors.back().getId() + 1;
    std::cout << centerString("Patient ID: ", MAX_LENGTH, false) << id << std::endl;

    std::string password;
    std::cin.ignore();
    std::cout << centerString("Enter the password: ", MAX_LENGTH, false);
    std::getline(std::cin, password);

    Doctor doctor(id, password);
    doctor.getInfoFromUser(MAX_LENGTH);
    this->doctors.push_back(doctor);
}

Doctor *Hospital::findDoctor(int id)
{
    for (auto &doctor : this->doctors)
    {
        if (doctor.getId() == id)
        {
            return &doctor;
        }
    }
    return nullptr;
}

Doctor Hospital::findAndShowDoctor(int id)
{
    const Doctor *doctor = findDoctor(id);
    if (doctor != nullptr)
    {
        std::cout << *doctor << std::endl;
    }
    else
    {
        std::cout << "Doctor not found!" << std::endl;
    }
    return *doctor;
}

Doctor *Hospital::authenticateDoctor(int id, std::string password)
{
    Doctor *doctor = findDoctor(id);
    if (doctor != nullptr && doctor->authenticate(password))
    {
        return doctor;
    }
    return nullptr;
}

// Write a CSV file of doctors. basic info and patients assigned in seprate two files
void Hospital::writeDoctorsData()
{
    std::ofstream doctorsFile("doctors.csv");
    std::ofstream patientsAssignedFile("patients_assigned.csv");

    if (doctorsFile.is_open() && patientsAssignedFile.is_open())
    {
        doctorsFile << "ID,Name,Age,Address,Phone Number,Specialization,Qualifications,Years of Experience,Password\n";
        patientsAssignedFile << "ID,Doctor ID,Patient ID,Assigned At\n";

        for (const auto &doctor : this->doctors)
        {
            doctorsFile << doctor.getId() << "," << doctor.getName() << "," << doctor.getAge() << "," << doctor.getAddress() << "," << doctor.getPhoneNumber() << "," << doctor.getSpecialization() << "," << doctor.getQualifications() << "," << doctor.getYearsOfExperience() << "," << doctor.getPassword() << "\n";

            for (const auto &patientAssigned : doctor.getPatientsAssigned())
            {
                patientsAssignedFile << patientAssigned.id << "," << doctor.getId() << "," << patientAssigned.patient->getId() << "," << patientAssigned.assignedAt << "\n";
            }
        }

        doctorsFile.close();
        patientsAssignedFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open the file." << std::endl;
    }
}
// -------------------------------- DOCTOR FUNCTIONS END --------------------------------

// -------------------------------- NURSE FUNCTIONS START --------------------------------
void Hospital::addNurse(int MAX_LENGTH)
{
    int id = 1;
    if (!this->nurses.empty())
        id = this->nurses.back().getId() + 1;
    std::cout << "Nurse ID: " << id << std::endl;

    std::string password;
    std::cin.ignore();
    std::cout << "Enter the password: ";
    std::getline(std::cin, password);

    Nurse nurse(id, password);
    nurse.getInfoFromUser(MAX_LENGTH);
    this->nurses.push_back(nurse);
}

Nurse *Hospital::findNurse(int id)
{
    for (auto &nurse : this->nurses)
    {
        if (nurse.getId() == id)
        {
            return &nurse;
        }
    }
    return nullptr;
}

Nurse Hospital::findAndShowNurse(int id)
{
    const Nurse *nurse = findNurse(id);
    if (nurse != nullptr)
    {
        std::cout << *nurse << std::endl;
    }
    else
    {
        std::cout << "Nurse not found!" << std::endl;
    }
    return *nurse;
}
// -------------------------------- NURSE FUNCTIONS END --------------------------------

// void Hospital::addRoom()
// {
//     Room room(this->rooms.back().getId() + 1);
//     room.getInfoFromUser();
//     this->rooms.push_back(room);
// }

// void Hospital::addAppointment()
// {
//     Appointment appointment(this->appointments.back().getId() + 1);
//     appointment.getInfoFromUser();
//     this->appointments.push_back(appointment);
// }

// Room* Hospital::findRoom(int id)
// {
//     for (auto &room : this->rooms)
//     {
//         if (room.getId() == id)
//         {
//             return &room;
//         }
//     }
//     return nullptr;
// }

// Appointment* Hospital::findAppointment(int id)
// {
//     for (auto &appointment : this->appointments)
//     {
//         if (appointment.getId() == id)
//         {
//             return &appointment;
//         }
//     }
//     return nullptr;
// }

std::string Hospital::centerString(const std::string &str, int width, bool center)
{
    int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
    if (padLen < 0)
    {
        padLen = 0;
    }
    std::string padding(padLen, ' ');
    return padding + str;
}
