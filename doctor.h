#ifndef DOCTOR_H
#define DOCTOR_H

#include <vector>
#include "person.h"
#include "patient_assigned.h"

class Doctor : public Person
{
protected:
    std::string specialization;
    std::string qualifications;
    int yearsOfExperience;
    std::vector<PatientAssigned> patientsAssigned;

public:
    // Call the parameterized constructor of Person class
    Doctor(int id, std::string password) : Person(id, password) {}

    // Overload the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Doctor &doctor);

    bool authenticate(std::string password) const; // Authenticate doctor
    void getInfoFromUser(int MAX_LENGTH);          // Get doctor info from user
    void assignPatient(Patient &patient);          // Assign patient to the doctor
    void assignPatient(int id, Patient &patient, Date assignedAt);
    int getAssignedPatient(int id) const;          // Get patient assigned by id
    void unassignPatient(int id);                  // Unassign patient from the doctor

    // Accessors
    std::string getSpecialization() const;
    std::string getQualifications() const;
    int getYearsOfExperience() const;
    std::vector<PatientAssigned> getPatientsAssigned() const;
};

#endif // DOCTOR_H