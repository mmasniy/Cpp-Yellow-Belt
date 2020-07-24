#pragma once

#include "date.h"
#include <set>
#include <map>

class Database {
    map<Date, set<string>> events;

public:
    void Add(const Date& date, const string& event);
    int FindIf(function<bool (Date, string)>) const;
    void Last()const;
    void Print(ostream& out) const;
    int RemoveIf(function<bool (Date, string)>);
};