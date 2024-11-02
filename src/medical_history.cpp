#include "medical_history.h"

// Overlaod << operator for vector of MedicalHistory
std::ostream &operator<<(std::ostream &out, const std::vector<MedicalHistory> &histories)
{
    out << Util::centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;
    out << Util::centerString("| " + Util::setPadding("ID", 2, 'c') + " | " + Util::setPadding("Current Medications", 20, 'c') + " | " + Util::setPadding("Allergies", 20, 'c') + " | " + Util::setPadding("Doctor Assigned", 20, 'c') + " | " + Util::setPadding("Room", 4, 'c') + " | " + Util::setPadding("Created At", 10, 'c') + " | " + Util::setPadding("Last Updated", 12, 'c') + " |") << std::endl;
    out << Util::centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;

    for (const auto &history : histories)
    {

        out << Util::centerString("| " + Util::setPadding(std::to_string(history.id), 2, 'c') + " | " + Util::setPadding(history.currentMedications, 20, 'l') + " | " + Util::setPadding(history.allergies, 20, 'l') + " | " + Util::setPadding(history.doctorAssigned, 20, 'l') + " | " + Util::setPadding(history.roomNumber, 4, 'c') + " | " + Util::setPadding(history.createdAt.toString(), 10, 'l') + " | " + Util::setPadding(history.lastUpdatedAt.toString(), 12, 'c') + " |") << std::endl;
        out << Util::centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;
    }
    return out;
}

// Overload << operator for MedicalHistory
std::ostream &operator<<(std::ostream &out, const MedicalHistory &history)
{
    out << Util::centerString("ID: " + std::to_string(history.id), 35, false) << std::endl;
    out << Util::centerString("Current Medications: " + history.currentMedications, 35, false) << std::endl;
    out << Util::centerString("Allergies: " + history.allergies, 35, false) << std::endl;
    out << Util::centerString("Doctor Assigned: " + history.doctorAssigned, 35, false) << std::endl;
    out << Util::centerString("Room Number: " + history.roomNumber, 35, false) << std::endl;
    out << Util::centerString("Created At: " + history.createdAt.toString(), 35, false) << std::endl;
    out << Util::centerString("Last Updated At: " + history.lastUpdatedAt.toString(), 35, false) << std::endl;

    return out;
}