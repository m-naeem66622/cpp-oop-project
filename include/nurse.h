#pragma once

#include <vector>
#include "person.h"
#include "patient_assigned.h"

class Nurse : public Person
{
protected:
    std::string department;
    std::vector<PatientAssigned> patientsAssigned;

public:
    // Call the parameterized constructor of Person class
    Nurse(int id, std::string password) : Person(id, password) {}
    Nurse(int id, std::string name, int age, std::string address, std::string phoneNumber, std::string password, std::string department) : Person(id, name, age, address, phoneNumber, password), department(department) {}

    // Overload the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Nurse &nurse);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<Nurse> &nurses);

    bool authenticate(std::string password) const; // Authenticate nurse
    void getInfoFromUser(int MAX_LENGTH);          // Get nurse info from user
    bool assignPatient(Patient &patient);          // Assign patient to the nurse
    void assignPatient(int id, Patient &patient, Date assignedAt);
    Patient *getAssignedPatient(int patientId) const; // Get assigned patient by id
    bool unassignPatient(int id);                     // Unassign patient from the nurse

    // Accessors
    std::string getDepartment() const;
    std::vector<PatientAssigned> getPatientsAssigned() const;
};