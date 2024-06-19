#ifndef PATIENT_H
#define PATIENT_H

#include <vector>
#include <iomanip>
#include "date.h"
#include "person.h"

struct MedicalHistory
{
    int id;
    std::string currentMedications;
    std::string allergies;
    std::string doctorAssigned;
    std::string roomNumber;
    Date createdAt;
    Date lastUpdatedAt;

    static std::string centerString(const std::string &str, int width = CONSOLE_WIDTH, bool center = true)
    {
        int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
        if (padLen < 0)
        {
            padLen = 0;
        }
        std::string padding(padLen, ' ');
        return padding + str;
    }

    static std::string setPadding(std::string str, int width, char align = 'c')
    {
        int length = str.length();
        if (length >= width)
            return str;
        int diff = width - length;
        int pad1 = diff / 2;
        int pad2 = diff - pad1;
        if (align == 'l')
            return str + std::string(diff, ' ');
        else if (align == 'r')
            return std::string(diff, ' ') + str;
        else
            return std::string(pad1, ' ') + str + std::string(pad2, ' ');
    }

    // Overlaod << operator
    // friend std::ostream &operator<<(std::ostream &out, const MedicalHistory &history);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<MedicalHistory> &histories)
    {
        out << centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;
        out << centerString("| " + setPadding("ID", 2, 'c') + " | " + setPadding("Current Medications", 20, 'c') + " | " + setPadding("Allergies", 20, 'c') + " | " + setPadding("Doctor Assigned", 20, 'c') + " | " + setPadding("Room", 4, 'c') + " | " + setPadding("Created At", 10, 'c') + " | " + setPadding("Last Updated", 12, 'c') + " |") << std::endl;
        out << centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;

        for (const auto &history : histories)
        {

            out << centerString("| " + setPadding(std::to_string(history.id), 2, 'c') + " | " + setPadding(history.currentMedications, 20, 'l') + " | " + setPadding(history.allergies, 20, 'l') + " | " + setPadding(history.doctorAssigned, 20, 'l') + " | " + setPadding(history.roomNumber, 4, 'c') + " | " + setPadding(history.createdAt.toString(), 10, 'l') + " | " + setPadding(history.lastUpdatedAt.toString(), 12, 'c') + " |") << std::endl;
            out << centerString("+----+----------------------+----------------------+----------------------+------+------------+--------------+") << std::endl;
        }
        return out;
    }

    friend std::ostream &operator<<(std::ostream &out, const MedicalHistory &history)
    {
        out << centerString("ID: " + std::to_string(history.id), 35, false) << std::endl;
        out << centerString("Current Medications: " + history.currentMedications, 35, false) << std::endl;
        out << centerString("Allergies: " + history.allergies, 35, false) << std::endl;
        out << centerString("Doctor Assigned: " + history.doctorAssigned, 35, false) << std::endl;
        out << centerString("Room Number: " + history.roomNumber, 35, false) << std::endl;
        out << centerString("Created At: " + history.createdAt.toString(), 35, false) << std::endl;
        out << centerString("Last Updated At: " + history.lastUpdatedAt.toString(), 35, false) << std::endl;

        return out;
    }
};

class Patient : public Person
{
protected:
    std::string bloodGroup;
    std::vector<MedicalHistory> medicalHistory;

private:
    MedicalHistory getMedicalHistoryFromUser(bool isNew); // Get medical history from user

public:
    // Call the parameterized constructor of Person class
    Patient(int id, std::string password) : Person(id, password) {}
    Patient(int id, std::string name, int age, std::string address, std::string phoneNumber, std::string password, std::string bloodGroup) : Person(id, name, age, address, phoneNumber, password), bloodGroup(bloodGroup) {}

    // Overload the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Patient &patient);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<Patient> &patients);

    // TODO - Seems to be bug in generating id for medical history while pushing in to start of vector

    bool authenticate(std::string password) const; // Authenticate patient
    void getInfoFromUser(int MAX_LENGTH);          // Get patient info from user
    void addMedicalHistory(std::string doctor);    // Add medical history
    void addMedicalHistory(MedicalHistory history);
    void addMedicalHistory(int id, std::string currentMedications, std::string allergies, std::string doctorAssigned, std::string roomNumber, Date createdAt, Date lastUpdatedAt);
    MedicalHistory *getMedicalHistoryById(int id) const;              // Get medical history by id
    MedicalHistory *updateMedicalHistory(int id, std::string doctor); // Update medical history by id
    MedicalHistory *removeMedicalHistory(int id);                     // Remove medical history by id

    // Accessors
    std::string getBloodGroup() const;
    std::vector<MedicalHistory> getMedicalHistory() const;
};

#endif // PATIENT_H