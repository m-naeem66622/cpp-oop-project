#pragma once

#include <vector>
#include "date.h"
#include "util.h"

struct MedicalHistory
{
    int id;
    std::string currentMedications;
    std::string allergies;
    std::string doctorAssigned;
    std::string roomNumber;
    Date createdAt;
    Date lastUpdatedAt;

    // Overlaod << operator
    // friend std::ostream &operator<<(std::ostream &out, const MedicalHistory &history);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<MedicalHistory> &histories);

    friend std::ostream &operator<<(std::ostream &out, const MedicalHistory &history);
};