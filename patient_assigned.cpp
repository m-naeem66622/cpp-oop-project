#include "patient_assigned.h"
#include <ostream>

// Overload the << operator to print the patient assigned
std::ostream &operator<<(std::ostream &out, const PatientAssigned &patientAssigned)
{
    out << "Patient Assigned ID: " << patientAssigned.id << std::endl;
    out << "Patient Assigned Date: " << patientAssigned.assignedAt << std::endl;
    out << "PATIENT: " << std::endl;
    out << *patientAssigned.patient;
    return out;
}

// Overload the << operator to print the vector of patients assigned
std::ostream &operator<<(std::ostream &out, const std::vector<PatientAssigned> &patientsAssigned)
{
    for (const auto &patientAssigned : patientsAssigned)
    {
        out << patientAssigned;
    }
    return out;
}