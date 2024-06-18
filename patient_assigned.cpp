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
    out << Patient::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;
    out << Patient::centerString("| " + MedicalHistory::setPadding("ID", 3, 'c') + " | " + MedicalHistory::setPadding("P_ID", 4, 'c') + " | " + MedicalHistory::setPadding("Name", 20, 'c') + " | " + MedicalHistory::setPadding("Age", 3, 'c') + " | " + MedicalHistory::setPadding("Phone Number", 12, 'c') + " | " + MedicalHistory::setPadding("Blood Group", 11, 'c') + " | " + MedicalHistory::setPadding("Assigned At", 11, 'c') + " |") << std::endl;
    out << Patient::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;

    for (const auto &assigned : patientsAssigned)
    {
        out << Patient::centerString("| " + MedicalHistory::setPadding(std::to_string(assigned.id), 3, 'c') + " | " + MedicalHistory::setPadding(std::to_string(assigned.patient->getId()), 4, 'c') + " | " + MedicalHistory::setPadding(assigned.patient->getName(), 20, 'l') + " | " + MedicalHistory::setPadding(std::to_string(assigned.patient->getAge()), 3, 'c') + " | " + MedicalHistory::setPadding(assigned.patient->getPhoneNumber(), 12, 'c') + " | " + MedicalHistory::setPadding(assigned.patient->getBloodGroup(), 11, 'c') + " | " + MedicalHistory::setPadding(assigned.assignedAt.toString(), 11, 'c') + " |") << std::endl;
        out << Patient::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;
    }
    return out;
}

// // Overload the << operator to print the vector of patients assigned
// std::ostream &operator<<(std::ostream &out, const std::vector<PatientAssigned> &patientsAssigned)
// {
//     for (const auto &patientAssigned : patientsAssigned)
//     {
//         out << patientAssigned;
//     }
//     return out;
// }