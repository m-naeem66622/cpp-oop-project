#ifndef PATIENT_ASSIGNED_H
#define PATIENT_ASSIGNED_H

#include "date.h"
#include "patient.h"

struct PatientAssigned
{
    int id;
    Patient *patient; // Pointer to the patient
    Date assignedAt;
};

std::ostream &operator<<(std::ostream &out, const PatientAssigned &patientAssigned);
std::ostream &operator<<(std::ostream &out, const std::vector<PatientAssigned> &patientsAssigned);

#endif // PATIENT_ASSIGNED_H