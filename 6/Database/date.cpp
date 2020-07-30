#include "date.h"

Date::Date(int new_year, int new_month, int new_day) {
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

constexpr tuple<const int &, const int &, const int &> Date::rank() const {
    return tie(year, month, day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.rank() == rhs.rank();
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return lhs.rank() < rhs.rank();
}

bool operator>(const Date& lhs, const Date& rhs) {
    return lhs.rank() > rhs.rank();
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
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
        return Date(year, month, day);
}