#pragma once

#include "date.h"
#include <set>
#include <map>

class Database {
    map<Date, set<string>> events;

public:
    void Add(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);
    void FindIf(const Date& date) const;
    void Last()const;
    void Print(ostream& out) const;
    void RemoveIf();
};