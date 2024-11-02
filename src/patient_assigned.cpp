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
    out << Util::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;
    out << Util::centerString("| " + Util::setPadding("ID", 3, 'c') + " | " + Util::setPadding("P_ID", 4, 'c') + " | " + Util::setPadding("Name", 20, 'c') + " | " + Util::setPadding("Age", 3, 'c') + " | " + Util::setPadding("Phone Number", 12, 'c') + " | " + Util::setPadding("Blood Group", 11, 'c') + " | " + Util::setPadding("Assigned At", 11, 'c') + " |") << std::endl;
    out << Util::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;

    for (const auto &assigned : patientsAssigned)
    {
        out << Util::centerString("| " + Util::setPadding(std::to_string(assigned.id), 3, 'c') + " | " + Util::setPadding(std::to_string(assigned.patient->getId()), 4, 'c') + " | " + Util::setPadding(assigned.patient->getName(), 20, 'l') + " | " + Util::setPadding(std::to_string(assigned.patient->getAge()), 3, 'c') + " | " + Util::setPadding(assigned.patient->getPhoneNumber(), 12, 'c') + " | " + Util::setPadding(assigned.patient->getBloodGroup(), 11, 'c') + " | " + Util::setPadding(assigned.assignedAt.toString(), 11, 'c') + " |") << std::endl;
        out << Util::centerString("+-----+------+----------------------+-----+--------------+-------------+-------------+") << std::endl;
    }
    return out;
}