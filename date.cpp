#include "date.h"

Date::Date()
{
    getCurrentDate();
}

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

void Date::getDate()
{
    std::cout << "Enter the year: ";
    std::cin >> year;
    std::cout << "Enter the month: ";
    std::cin >> month;
    std::cout << "Enter the day: ";
    std::cin >> day;
}

Date Date::getCurrentDate()
{
    Date date;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    date.year = 1900 + ltm->tm_year;
    date.month = 1 + ltm->tm_mon;
    date.day = ltm->tm_mday;
    return date;
}

void Date::displayDate() const
{
    std::cout << "Medical History Date: " << day << "/" << month << "/" << year << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Date &date)
{
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}
