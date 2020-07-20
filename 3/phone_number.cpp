#include <iostream>
#include <sstream>
#include "phone_number.h"

void GetNumber(stringstream& number, string& string_code, const char delim = '\n') {
    getline(number, string_code, delim);
    if (string_code.empty()) {
        throw invalid_argument("Not found need delimiter");
    }
}

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream number;
    number << international_number;
    if (number) {
        if (number.peek() != '+') {
            throw invalid_argument("String does not start with +");
        }
        number.ignore(1);
        GetNumber(number, country_code_, '-');
    }
    if (number) {
        GetNumber(number, city_code_, '-');
    }
    if (number) {
        GetNumber(number, local_number_);
    }
    else {
        throw invalid_argument("String isn`t valid");
    }

}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber()  const{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

int main() {
    PhoneNumber num ("+380-68-");

    cout << num.GetInternationalNumber() << endl;
}
