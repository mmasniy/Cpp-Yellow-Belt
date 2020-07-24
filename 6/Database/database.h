#pragma once

#include "date.h"
#include <set>
#include <map>

class Database {
    map<Date, set<string>> events;
    map<Date, vector<string>> hrono_events;

public:
    void Add(const Date& date, const string& event);
    void Last()const;
    void Print(ostream& out) const;
    template <class Func> int RemoveIf(Func predicate);

    template<class Func>
    int FindIf(Func predicate);
};