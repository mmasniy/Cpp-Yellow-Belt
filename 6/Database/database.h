#pragma once

#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "date.h"

string DataToString(const Date& date);

class Database {
    map<Date, set<string>> events;
    map<Date, vector<string>> hrono_events;

public:
    void Add(const Date& date, const string& event);
    void Print(ostream& out) const;
    int RemoveIf(const function<bool(const Date& date, const string& event)>& predicate);
    vector<string> FindIf(const function<bool(const Date& date, const string& event)>& predicate) const;
    [[nodiscard]] string Last(const Date& date) const;
};
