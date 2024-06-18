#ifndef NURSE_H
#define NURSE_H

#include <vector>
#include "date.h"
#include "person.h"
#include "patient_assigned.h"
#include "patient.h"

class Nurse : public Person
{
protected:
    std::string department;
    std::vector<PatientAssigned> patientsAssigned;

public:
    // Call the parameterized constructor of Person class
    Nurse(int id, std::string password) : Person(id, password) {}

    // Overload the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Nurse &nurse);

    void getInfoFromUser(int MAX_LENGTH); // Get nurse info from user
    void assignPatient(Patient &patient); // Assign patient to the nurse
    int getAssignedPatient(int id) const; // Get patient assigned by id
    void unassignPatient(int id);         // Unassign patient from the nurse
};

#endif // NURSE_H