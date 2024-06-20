#include "nurse.h"

// Overload the stream insertion operator
std::ostream &operator<<(std::ostream &out, const Nurse &nurse)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(nurse);

    // Print the nurse information
    out << Nurse::centerString("Department: " + nurse.department, 35, false) << std::endl;
    out << Nurse::centerString("Patients Assigned: " + std::to_string(nurse.patientsAssigned.size()), 35, false) << std::endl;
    return out;
}

// Overload the stream insertion operator
std::ostream &operator<<(std::ostream &out, const std::vector<Nurse> &nurses)
{
    out << Nurse::centerString("+-----+----------------------+-----+--------------+----------------------+-----------------------------------+") << std::endl;
    out << Nurse::centerString("| " + MedicalHistory::setPadding("ID", 3, 'c') + " | " + MedicalHistory::setPadding("Name", 20, 'c') + " | " + MedicalHistory::setPadding("Age", 3, 'c') + " | " + MedicalHistory::setPadding("Phone Number", 12, 'c') + " | " + MedicalHistory::setPadding("Department", 20, 'c') + " | " + MedicalHistory::setPadding("Address", 33, 'l') + " |") << std::endl;
    out << Nurse::centerString("+-----+----------------------+-----+--------------+----------------------+-----------------------------------+") << std::endl;

    for (const auto &nurse : nurses)
    {
        out << Nurse::centerString("| " + MedicalHistory::setPadding(std::to_string(nurse.id), 3, 'c') + " | " + MedicalHistory::setPadding(nurse.name, 20, 'l') + " | " + MedicalHistory::setPadding(std::to_string(nurse.age), 3, 'c') + " | " + MedicalHistory::setPadding(nurse.phoneNumber, 12, 'c') + " | " + MedicalHistory::setPadding(nurse.department, 20, 'c') + " | " + MedicalHistory::setPadding(nurse.address, 33, 'l') + " |") << std::endl;
        out << Nurse::centerString("+-----+----------------------+-----+--------------+----------------------+-----------------------------------+") << std::endl;
    }
    return out;
}

// Authenticate nurse
bool Nurse::authenticate(std::string password) const
{
    return password == this->password;
}

// Get nurse info from user
void Nurse::getInfoFromUser(int MAX_LENGTH)
{
    Person::getInfoFromUser(MAX_LENGTH);

    // std::cin.ignore();
    std::cout << centerString("Enter the department: ", MAX_LENGTH, false);
    std::getline(std::cin, department);
}

// Assign patient to the nurse - with 1 argument (default)
bool Nurse::assignPatient(Patient &patient)
{
    if (getAssignedPatient(patient.getId()) != nullptr)
        return false;

    PatientAssigned patientAssigned;
    patientAssigned.patient = &patient;
    patientAssigned.assignedAt = Date();

    if (patientsAssigned.size() == 0)
        patientAssigned.id = 1;
    else
        patientAssigned.id = patientsAssigned.back().id + 1;

    patientsAssigned.push_back(patientAssigned);

    return true;
}

// Assign patient to the nurse - with 3 arguments
void Nurse::assignPatient(int id, Patient &patient, Date assignedAt)
{
    PatientAssigned patientAssigned = {id, &patient, assignedAt};

    patientsAssigned.push_back(patientAssigned);
}

// Get patient assigned by id
Patient *Nurse::getAssignedPatient(int patientId) const
{
    for (auto &patientAssigned : patientsAssigned)
    {
        if (patientAssigned.patient->getId() == patientId)
        {
            return patientAssigned.patient;
        }
    }

    return nullptr;
}

// Unassign patient from the nurse
bool Nurse::unassignPatient(int patientId)
{
    for (auto it = patientsAssigned.begin(); it != patientsAssigned.end(); ++it)
    {
        if (it->patient->getId() == patientId)
        {
            patientsAssigned.erase(it);
            return true;
        }
    }

    return false;
}

// Accessors
std::string Nurse::getDepartment() const
{
    return department;
}

std::vector<PatientAssigned> Nurse::getPatientsAssigned() const
{
    return patientsAssigned;
}