#include "patient.h"

// Overload the << operator to print the patient information
std::ostream &operator<<(std::ostream &out, const Patient &patient)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(patient);

    // Print the patient information
    out << Patient::centerString("Blood Group: " + patient.bloodGroup, 35, false) << std::endl;
    return out;
}

// Overload the << operator to print the medical history
std::ostream &operator<<(std::ostream &out, const MedicalHistory &history)
{
    out << "Medical History ID: " << history.id << std::endl;
    out << "Medical History Date: " << history.createdAt << std::endl;
    out << "Current Medications: " << history.currentMedications << std::endl;
    out << "Allergies: " << history.allergies << std::endl;
    out << "Doctor Assigned: " << history.doctorAssigned << std::endl;
    out << "Room Number: " << history.roomNumber << std::endl;
    return out;
}

// Overload the << operator to print the vector of medical history
std::ostream &operator<<(std::ostream &out, const std::vector<MedicalHistory> &histories)
{
    for (const auto &history : histories)
    {
        out << history;
    }
    return out;
}

// Authenticate patient
bool Patient::authenticate(std::string password) const
{
    return password == this->password;
}

// Add medical history
MedicalHistory Patient::getMedicalHistoryFromUser()
{
    MedicalHistory history;

    if (medicalHistory.size() == 0)
        history.id = 1;
    else
        history.id = medicalHistory.front().id - 1;

    Date current_date;

    history.createdAt = current_date;
    history.lastUpdatedAt = current_date;

    std::cout << "Enter the current medications: ";
    std::cin.ignore();
    std::getline(std::cin, history.currentMedications);

    std::cout << "Enter the allergies: ";
    std::getline(std::cin, history.allergies);

    std::cout << "Enter the doctor assigned: ";
    std::getline(std::cin, history.doctorAssigned);

    std::cout << "Enter the room number: ";
    std::getline(std::cin, history.roomNumber);

    return history;
}

// Get patient info from user
void Patient::getInfoFromUser(int MAX_LENGTH)
{
    // Call the base class function to get the common information
    Person::getInfoFromUser(MAX_LENGTH);

    std::cout << centerString("Enter the blood group: ", MAX_LENGTH, false);
    std::cin >> bloodGroup;
}

// Add medical history - default
void Patient::addMedicalHistory()
{
    MedicalHistory history = getMedicalHistoryFromUser();

    // Add the medical history to the start of the vector
    medicalHistory.insert(medicalHistory.begin(), history);
}

// Add medical history - parameterized
void Patient::addMedicalHistory(int id, std::string currentMedications, std::string allergies, std::string doctorAssigned, std::string roomNumber, Date createdAt, Date lastUpdatedAt)
{
    MedicalHistory history;
    history.id = id;
    history.currentMedications = currentMedications;
    history.allergies = allergies;
    history.doctorAssigned = doctorAssigned;
    history.roomNumber = roomNumber;
    history.createdAt = createdAt;
    history.lastUpdatedAt = lastUpdatedAt;

    // Add the medical history to the start of the vector
    medicalHistory.insert(medicalHistory.begin(), history);
}

// Get medical history by id
int Patient::getMedicalHistory(int id) const
{
    for (const auto &history : medicalHistory)
    {
        if (history.id == id)
        {
            std::cout << history;
            return 1; // 1 if found
        }
    }
    std::cout << "Medical history not found." << std::endl;
    return 0; // 0 if not found
}

// Update medical history by id
void Patient::updateMedicalHistory(int id)
{
    bool found = getMedicalHistory(id);
    if (!found)
        return;

    std::cout << "CURRENT MEDICAL HISTORY" << std::endl;
    std::cout << medicalHistory[id - 1];
    std::cout << std::endl
              << "UPDATE MEDICAL HISTORY" << std::endl;
    medicalHistory[id - 1] = getMedicalHistoryFromUser();
}

// Remove medical history by id
void Patient::removeMedicalHistory(int id)
{
    bool found = getMedicalHistory(id);
    if (!found)
        return;

    medicalHistory.erase(medicalHistory.begin() + id - 1);
}

// Accessors
std::string Patient::getBloodGroup() const
{
    return bloodGroup;
}

std::vector<MedicalHistory> Patient::getMedicalHistory() const
{
    return medicalHistory;
}