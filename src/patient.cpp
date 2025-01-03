#include "patient.h"

// Overload the << operator to print the patient information
std::ostream &operator<<(std::ostream &out, const Patient &patient)
{
    // Call the << operator of the base class
    out << static_cast<const Person &>(patient);

    // Print the patient information
    out << Util::centerString("Blood Group: " + patient.bloodGroup, 35, false) << std::endl;
    return out;
}

// Overload the << operator to print the vector of patients
std::ostream &operator<<(std::ostream &out, const std::vector<Patient> &patients)
{
    out << Util::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;
    out << Util::centerString("| " + Util::setPadding("ID", 3, 'c') + " | " + Util::setPadding("Name", 20, 'c') + " | " + Util::setPadding("Age", 3, 'c') + " | " + Util::setPadding("Phone Number", 12, 'c') + " | " + Util::setPadding("Blood Group", 11, 'c') + " | " + Util::setPadding("Address", 34, 'l') + " |") << std::endl;
    out << Util::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;

    for (const auto &patient : patients)
    {
        out << Util::centerString("| " + Util::setPadding(std::to_string(patient.id), 3, 'c') + " | " + Util::setPadding(patient.name, 20, 'l') + " | " + Util::setPadding(std::to_string(patient.age), 3, 'c') + " | " + Util::setPadding(patient.phoneNumber, 12, 'c') + " | " + Util::setPadding(patient.bloodGroup, 11, 'c') + " | " + Util::setPadding(patient.address, 34, 'l') + " |") << std::endl;
        out << Util::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;
    }
    return out;
}

// Authenticate patient
bool Patient::authenticate(std::string password) const
{
    return password == this->password;
}

// Add medical history
MedicalHistory Patient::getMedicalHistoryFromUser(bool isNew = true)
{
    MedicalHistory history;

    if (medicalHistory.size() == 0)
        history.id = 1;
    else
        history.id = medicalHistory.front().id + 1;

    Date current_date;
    if (isNew)
        history.createdAt = current_date;
    history.lastUpdatedAt = current_date;

    std::cout << Util::centerString("Enter the current medications: ", 35, false);
    std::cin.ignore();
    std::getline(std::cin, history.currentMedications);

    std::cout << Util::centerString("Enter the allergies: ", 35, false);
    std::getline(std::cin, history.allergies);

    std::cout << Util::centerString("Enter the room number: ", 35, false);
    std::getline(std::cin, history.roomNumber);

    return history;
}

// Get patient info from user
void Patient::getInfoFromUser(int MAX_LENGTH)
{
    // Call the base class function to get the common information
    Person::getInfoFromUser(MAX_LENGTH);

    std::cout << Util::centerString("Enter the blood group: ", MAX_LENGTH, false);
    std::cin >> bloodGroup;
}

// Add medical history - default
void Patient::addMedicalHistory(std::string doctor)
{
    MedicalHistory history = getMedicalHistoryFromUser();

    history.doctorAssigned = doctor;

    // Add the medical history to the start of the vector
    medicalHistory.insert(medicalHistory.begin(), history);
}

// Add medical history - parameterized
void Patient::addMedicalHistory(MedicalHistory history)
{
    // Add the medical history to the start of the vector
    medicalHistory.insert(medicalHistory.begin(), history);
}

// Add medical history - parameterized
void Patient::addMedicalHistory(int id, std::string currentMedications, std::string allergies, std::string doctorAssigned, std::string roomNumber, Date createdAt, Date lastUpdatedAt)
{
    MedicalHistory history = {id, currentMedications, allergies, doctorAssigned, roomNumber, createdAt, lastUpdatedAt};

    // Add the medical history to the start of the vector
    // if (medicalHistory.size() == 0)
    //     medicalHistory.push_back(history);
    // else
    medicalHistory.insert(medicalHistory.begin(), history);
}

// Get medical history by id
MedicalHistory *Patient::getMedicalHistoryById(int id) const
{
    for (const auto &history : medicalHistory)
    {
        if (history.id == id)
            return const_cast<MedicalHistory *>(&history);
    }
    return nullptr;
}

// Update medical history by id
MedicalHistory *Patient::updateMedicalHistory(int id, std::string doctor)
{
    // Get the medical history by id
    MedicalHistory *history = getMedicalHistoryById(id);

    // Hold the creation date to update the history object
    Date createdAt = history->createdAt;

    if (history == nullptr)
        return nullptr;

    MedicalHistory updatedHistory = getMedicalHistoryFromUser(false);

    updatedHistory.createdAt = createdAt;
    updatedHistory.doctorAssigned = doctor;

    // Update the medical history
    *history = updatedHistory;

    return history;
}

// Remove medical history by id
MedicalHistory *Patient::removeMedicalHistory(int id)
{
    // Get the medical history by id
    MedicalHistory *history = getMedicalHistoryById(id);

    if (history == nullptr)
        return nullptr;

    for (auto it = medicalHistory.begin(); it != medicalHistory.end(); ++it)
    {
        if (it->id == id)
        {
            medicalHistory.erase(it);
            break;
        }
    }

    return history;
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