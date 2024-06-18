#include <limits>
#include "person.h"

Person::Person(int id, std::string password)
{
    this->id = id;
    this->password = password;
    name = "Unknown";
    age = 0;
    address = "Unknown";
    phoneNumber = "Unknown";
}

Person::Person(int id, std::string name, int age, std::string address, std::string phoneNumber, std::string password)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->password = password;
}

std::ostream &operator<<(std::ostream &out, const Person &person)
{
    int unsigned MAX_LENGTH = 35;
    out << Person::centerString("ID: " + std::to_string(person.id), MAX_LENGTH, false) << std::endl;
    out << Person::centerString("Name: " + person.name, MAX_LENGTH, false) << std::endl;
    out << Person::centerString("Age: " + std::to_string(person.age), MAX_LENGTH, false) << std::endl;
    out << Person::centerString("Address: " + person.address, MAX_LENGTH, false) << std::endl;
    out << Person::centerString("Phone Number: " + person.phoneNumber, MAX_LENGTH, false) << std::endl;
    return out;
}

void Person::getInfoFromUser(int MAX_LENGTH)
{
    // std::cin.ignore();
    std::cout << centerString("Enter the name: ", MAX_LENGTH, false);
    std::getline(std::cin, name);

    std::cout << centerString("Enter the age: ", MAX_LENGTH, false);
    while (!(std::cin >> age) || age < 0)
    {
        std::cout << std::endl
                  << centerString("Invalid input. Please enter a valid age: ");
        // Clear error flag
        std::cin.clear();
        // Ignore the rest of the current input line up to newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();
    std::cout << centerString("Enter the address: ", MAX_LENGTH, false);
    std::getline(std::cin, address);

// Label to redirect here if the phone number is invalid
retry_Phone_Number:
    std::cout << centerString("Enter the phone number (xxxx xxxxxxx): ", MAX_LENGTH, false);
    std::getline(std::cin, phoneNumber);
    try
    {
        if (phoneNumber.length() != 12)
        {
            throw std::invalid_argument(centerString("Invalid phone number. Please enter a valid phone number: \n"));
        }

        // Check if the phone number is in the format xxxx xxxxxxx
        // If it is seprated by a space
        if (phoneNumber[4] != ' ')
        {
            throw std::invalid_argument(centerString("Invalid phone number. Please enter a valid phone number: \n"));
        }

        // Check if the phone number contains only digits expect the space
        for (int i = 0; i < 12; i++)
        {
            if (i == 4)
            {
                continue;
            }
            if (!isdigit(phoneNumber[i]))
            {
                throw std::invalid_argument(centerString("Invalid phone number. Please enter a valid phone number: \n"));
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what();
        goto retry_Phone_Number; // Redirect to the label, i.e line 42
    }
}

std::string Person::centerString(const std::string &str, int width, bool center)
{
    int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
    if (padLen < 0)
    {
        padLen = 0;
    }
    std::string padding(padLen, ' ');
    return padding + str;
}

// Accessors
int Person::getId() const
{
    return id;
}

std::string Person::getName() const
{
    return name;
}

int Person::getAge() const
{
    return age;
}

std::string Person::getAddress() const
{
    return address;
}

std::string Person::getPhoneNumber() const
{
    return phoneNumber;
}

std::string Person::getPassword() const
{
    return password;
}