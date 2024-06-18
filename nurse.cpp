#include "nurse.h"

// Overload the stream insertion operator
std::ostream &operator<<(std::ostream &out, const Nurse &nurse)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(nurse);

    // Print the nurse information
    out << "Department: " << nurse.department << std::endl;
    out << "Patients Assigned: " << nurse.patientsAssigned.size() << std::endl;
    return out;
}

// Get nurse info from user
void Nurse::getInfoFromUser(int MAX_LENGTH)
{
    Person::getInfoFromUser(MAX_LENGTH);

    std::cin.ignore();
    std::cout << "Enter the department: ";
    std::getline(std::cin, department);
}

// Assign patient to the nurse
void Nurse::assignPatient(Patient &patient)
{
    PatientAssigned patientAssigned;

    if (patientsAssigned.size() == 0)
        patientAssigned.id = 1;
    else
        patientAssigned.id = patientsAssigned.back().id + 1;

    patientAssigned.patient = &patient;
    Date current_date;
    patientAssigned.assignedAt = current_date;
    patientsAssigned.push_back(patientAssigned);
}

// Get patient assigned by id
int Nurse::getAssignedPatient(int id) const
{
    for (const auto &patientAssigned : patientsAssigned)
    {
        if (patientAssigned.id == id)
        {
            std::cout << patientAssigned;
            return 1; // 1 if found
        }
    }
    std::cout << "Patient not found." << std::endl;
    return 0; // 0 if not found
}

// Unassign patient from the nurse
void Nurse::unassignPatient(int id)
{
    bool found = getAssignedPatient(id);
    if (!found)
        return;

    patientsAssigned.erase(patientsAssigned.begin() + id - 1);
}