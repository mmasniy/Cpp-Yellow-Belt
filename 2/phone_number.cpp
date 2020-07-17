#include <iostream>
#include <sstream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string &international_number) {

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


