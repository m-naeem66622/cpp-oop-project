#include <limits>
#include "doctor.h"

// Overload the << operator to print the doctor information
std::ostream &operator<<(std::ostream &out, const Doctor &doctor)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(doctor);

    // Print the doctor information
    out << Doctor::centerString("Specialization: " + doctor.specialization, 35, false) << std::endl;
    out << Doctor::centerString("Qualifications: " + doctor.qualifications, 35, false) << std::endl;
    out << Doctor::centerString("Years of Experience: " + std::to_string(doctor.yearsOfExperience), 35, false) << std::endl;
    out << Doctor::centerString("Patients Assigned: " + std::to_string(doctor.patientsAssigned.size()), 35, false) << std::endl;
    return out;
}

// Overload the << operator to print the vector of patients

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
bool Doctor::assignPatient(Patient &patient)
{
    // Debugging
    std::cout << "In to assignPatient\n";
    if (getAssignedPatient(patient.getId()) != nullptr)
        return false;

    // Debugging
    std::cout << "Patient not assigned\n";

    std::cout << "Creating patientAssigned\n";

    PatientAssigned patientAssigned;

    // Debugging
    std::cout << "Created patientAssigned\n";

    patientAssigned.patient = &patient;

    // Debugging
    std::cout << "Created date\n";
    patientAssigned.assignedAt = Date();

    if (patientsAssigned.size() == 0)
        patientAssigned.id = 1;
    else
        patientAssigned.id = patientsAssigned.back().id + 1;

    // Debugging
    std::cout << "ID: " << id << std::endl;

    patientsAssigned.push_back(patientAssigned);

    // Debugging
    std::cout << "Patient assigned\n";

    return true;
}

// Assign patient to the doctor - with 3 arguments
void Doctor::assignPatient(int id, Patient &patient, Date assignedAt)
{
    PatientAssigned patientAssigned = {id, &patient, assignedAt};

    patientsAssigned.push_back(patientAssigned);
}

// Get assigned patient by id
Patient *Doctor::getAssignedPatient(int patientId) const
{
    for (const auto &patientAssigned : patientsAssigned)
    {
        if (patientAssigned.patient->getId() == patientId)
        {
            // Debugging
            // std::cout << "Patient found\n";
            return patientAssigned.patient;
        }
    }

    // Debugging
    std::cout << "Patient not found\n";
    return nullptr;
}

// Unassign patient from the doctor
bool Doctor::unassignPatient(int patientId)
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
