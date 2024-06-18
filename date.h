#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);
    Date(std::string date);
    void getDateFromUser();
    Date getCurrentDate();
    void displayDate() const;
    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const Date &date);
};

#endif // DATE_H