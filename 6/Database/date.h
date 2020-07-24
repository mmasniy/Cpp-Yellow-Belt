#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <iomanip>
#include <sstream>

using namespace std;

class Date {
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0){
    }

    Date(int new_day, int new_month, int new_year);

    [[maybe_unused]] void PrintDate() const;
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);

    friend bool operator>=(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);

    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);

private:
    [[nodiscard]] constexpr tuple<const int &, const int &, const int &> rank() const;
};

Date ParseDate(istringstream& input);
