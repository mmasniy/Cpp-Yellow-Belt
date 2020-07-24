#include "date.h"

Date::Date(int new_day, int new_month, int new_year) {
    year = new_year;
    if (new_month < 1 || new_month > 12) {
        throw invalid_argument("Month value is invalid: " + to_string(new_month));
    }
    else {
        month = new_month;
    }

    if (new_day < 1 || new_day > 31) {
        throw invalid_argument("Day value is invalid: " + to_string(new_day));
    }
    else {
        day = new_day;
    }
}

[[maybe_unused]] void Date::PrintDate() const{
    cout << setw(4) << setfill('0') << GetYear() << "-"
         << setw(2) << setfill('0') << GetMonth() << "-"
         << setw(2) << setfill('0') << GetDay();
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() == rhs.GetDay();
        }
        return false;
    }
    return false;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth()== rhs.GetMonth()){
            return lhs.GetDay() < rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

[[maybe_unused]] Date ParseDate(istringstream& input) {
    int day, month, year;
        if (!(input >> year)) {
            string error = "Wrong date format: year";
            throw invalid_argument(error);
        }
        input.ignore(1);
        if (!(input >> month)) {
            string error = "Wrong date format: month";
            throw invalid_argument(error);
        }
        input.ignore(1);
        if (!(input >> day)) {
            string error = "Wrong date format: day";
            throw invalid_argument(error);
        }
        if ((input.peek() != EOF)) {
            string error = "Wrong date format: year.month.day";
            throw invalid_argument(error);
        }
        return Date(day, month, year);
}