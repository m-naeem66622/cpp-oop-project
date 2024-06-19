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

// Overload the << operator to print the vector of patients
std::ostream &operator<<(std::ostream &out, const std::vector<Patient> &patients)
{
    out << Patient::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;
    out << Patient::centerString("| " + MedicalHistory::setPadding("ID", 3, 'c') + " | " + MedicalHistory::setPadding("Name", 20, 'c') + " | " + MedicalHistory::setPadding("Age", 3, 'c') + " | " + MedicalHistory::setPadding("Phone Number", 12, 'c') + " | " + MedicalHistory::setPadding("Blood Group", 11, 'c') + " | " + MedicalHistory::setPadding("Address", 34, 'l') + " |") << std::endl;
    out << Patient::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;

    for (const auto &patient : patients)
    {
        out << Patient::centerString("| " + MedicalHistory::setPadding(std::to_string(patient.id), 3, 'c') + " | " + MedicalHistory::setPadding(patient.name, 20, 'l') + " | " + MedicalHistory::setPadding(std::to_string(patient.age), 3, 'c') + " | " + MedicalHistory::setPadding(patient.phoneNumber, 12, 'c') + " | " + MedicalHistory::setPadding(patient.bloodGroup, 11, 'c') + " | " + MedicalHistory::setPadding(patient.address, 34, 'l') + " |") << std::endl;
        out << Patient::centerString("+-----+----------------------+-----+--------------+-------------+------------------------------------+") << std::endl;
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
    // MedicalHistory history;
    MedicalHistory history = {0, "", "", "", "", Date(), Date()};

    if (medicalHistory.size() == 0)
        history.id = 1;
    else
        history.id = medicalHistory.front().id + 1;

    Date current_date;

    history.createdAt = current_date;
    history.lastUpdatedAt = current_date;

    std::cout << centerString("Enter the current medications: ", 35, false);
    std::cin.ignore();
    std::getline(std::cin, history.currentMedications);

    std::cout << centerString("Enter the allergies: ", 35, false);
    std::getline(std::cin, history.allergies);

    std::cout << centerString("Enter the doctor assigned: ", 35, false);
    std::getline(std::cin, history.doctorAssigned);

    std::cout << centerString("Enter the room number: ", 35, false);
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
int Patient::getMedicalHistoryById(int id) const
{
    for (const auto &history : medicalHistory)
    {
        if (history.id == id)
        {
            // std::cout << history;
            return 1; // 1 if found
        }
    }
    std::cout << "Medical history not found." << std::endl;
    return 0; // 0 if not found
}

// Update medical history by id
void Patient::updateMedicalHistory(int id)
{
    bool found = getMedicalHistoryById(id);
    if (!found)
        return;

    std::cout << "CURRENT MEDICAL HISTORY" << std::endl;
    // std::cout << medicalHistory[id - 1];
    std::cout << std::endl
              << "UPDATE MEDICAL HISTORY" << std::endl;
    medicalHistory[id - 1] = getMedicalHistoryFromUser();
}

// Remove medical history by id
void Patient::removeMedicalHistory(int id)
{
    bool found = getMedicalHistoryById(id);
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