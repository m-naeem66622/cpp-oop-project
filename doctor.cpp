#include <limits>
#include "doctor.h"

// Overload the << operator to print the doctor information
std::ostream &operator<<(std::ostream &out, const Doctor &doctor)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(doctor);

    // Print the doctor information
    out << "Specialization: " << doctor.specialization << std::endl;
    out << "Qualifications: " << doctor.qualifications << std::endl;
    out << "Years of Experience: " << doctor.yearsOfExperience << std::endl;
    out << "Patients Assigned: " << std::endl;
    out << doctor.patientsAssigned.size() << std::endl;
    return out;
}

// Authenticate doctor
bool Doctor::authenticate(std::string password) const
{
    return password == this->password;
}

// Get doctor info from user
void Doctor::getInfoFromUser(int MAX_LENGTH)
{
    Person::getInfoFromUser(MAX_LENGTH);

    // std::cin.ignore();
    std::cout << centerString("Enter the specialization: ", MAX_LENGTH, false);
    std::getline(std::cin, specialization);

    // std::cin.ignore();
    std::cout << centerString("Enter the qualifications: ", MAX_LENGTH, false);
    std::getline(std::cin, qualifications);

    std::cout << centerString("Enter the years of experience: ", MAX_LENGTH, false);
    while (!(std::cin >> yearsOfExperience) || yearsOfExperience < 0)
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid experience: ", MAX_LENGTH, false);
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Assign patient to the doctor - with 1 argument (default)
void Doctor::assignPatient(Patient &patient)
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

// Assign patient to the doctor - with 3 arguments
void Doctor::assignPatient(int id, Patient &patient, Date assignedAt)
{
    PatientAssigned patientAssigned;

    patientAssigned.id = id;
    patientAssigned.patient = &patient;
    patientAssigned.assignedAt = assignedAt;
    patientsAssigned.push_back(patientAssigned);
}

// Get patient assigned by id
int Doctor::getAssignedPatient(int id) const
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

// Unassign patient from the doctor
void Doctor::unassignPatient(int id)
{
    bool found = getAssignedPatient(id);
    if (!found)
        return;

    patientsAssigned.erase(patientsAssigned.begin() + id - 1);
}

// Accessors
std::string Doctor::getSpecialization() const
{
    return specialization;
}

std::string Doctor::getQualifications() const
{
    return qualifications;
}

int Doctor::getYearsOfExperience() const
{
    return yearsOfExperience;
}

std::vector<PatientAssigned> Doctor::getPatientsAssigned() const
{
    return patientsAssigned;
}
