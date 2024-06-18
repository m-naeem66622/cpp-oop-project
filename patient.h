#ifndef PATIENT_H
#define PATIENT_H

#include <vector>
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
};

class Patient : public Person
{
protected:
    std::string bloodGroup;
    std::vector<MedicalHistory> medicalHistory;

private:
    MedicalHistory getMedicalHistoryFromUser(); // Get medical history from user

public:
    // Call the parameterized constructor of Person class
    Patient(int id, std::string password) : Person(id, password) {}
    Patient(int id, std::string name, int age, std::string address, std::string phoneNumber, std::string password, std::string bloodGroup) : Person(id, name, age, address, phoneNumber, password), bloodGroup(bloodGroup) {}

    // Overload the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Patient &patient);
    friend std::ostream &operator<<(std::ostream &out, const MedicalHistory &history);
    friend std::ostream &operator<<(std::ostream &out, const std::vector<MedicalHistory> &histories);

    // TODO - Seems to be bug in generating id for medical history while pushing in to start of vector

    bool authenticate(std::string password) const; // Authenticate patient
    void getInfoFromUser(int MAX_LENGTH);          // Get patient info from user
    void addMedicalHistory();                      // Add medical history
    void addMedicalHistory(int id, std::string currentMedications, std::string allergies, std::string doctorAssigned, std::string roomNumber, Date createdAt, Date lastUpdatedAt);
    int getMedicalHistory(int id) const; // Get medical history by id
    void updateMedicalHistory(int id);   // Update medical history by id
    void removeMedicalHistory(int id);   // Remove medical history by id

    // Accessors
    std::string getBloodGroup() const;
    std::vector<MedicalHistory> getMedicalHistory() const;
};

#endif // PATIENT_H