#pragma once

#include <iostream>
#include <string>
#include "util.h"

class Person
{
protected:
    int id;
    std::string name;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string password;

public:
    Person(int id, std::string password); // Parameterized constructor - 2 arguments
    Person(int id, std::string name, int age, std::string address, std::string phoneNumber, std::string password); // Parameterized constructor - 6 arguments

    friend std::ostream &operator<<(std::ostream &out, const Person &person);

    void getInfoFromUser(int MAX_LENGTH);

    // Accessors
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getPassword() const;

private:
    Person(); // Private default constructor
};