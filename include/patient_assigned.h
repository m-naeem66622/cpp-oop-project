#pragma once

#include "date.h"
#include "patient.h"

struct PatientAssigned
{
    int id;
    Patient *patient; // Pointer to the patient
    Date assignedAt;

    // PatientAssigned(): id(0), patient(nullptr), assignedAt(Date()) {}
    // PatientAssigned(int id, Patient *patient, Date assignedAt): id(id), patient(patient), assignedAt(assignedAt) {}

    friend std::ostream &operator<<(std::ostream &out, const PatientAssigned &patientAssigned);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<PatientAssigned> &patientsAssigned);
};