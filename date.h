#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);
    void getDate();
    Date getCurrentDate();
    void displayDate() const;
    friend std::ostream &operator<<(std::ostream &out, const Date &date);
};

#endif // DATE_H