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
    template <class Function>
    int RemoveIf(Function predicate) {
        int count = 0;

        for (auto& [key, value] : events) {
            auto buffer = value;
            for (auto& event : buffer) {
                if (predicate(key, event)) {
                    value.erase(event);
                }
            }
        }

        for (auto& [key, value] : hrono_events) {
            Date date = key;
            auto it = stable_partition(value.begin(), value.end(),
                                       [predicate, date](const string &event) {
                                           return !predicate(date, event);
                                       });
            count += value.end() - it;
            value.erase(it, value.end());
        }
        auto hrono_events_ = hrono_events;
        for (const auto& [key, value] : hrono_events_) {
            if (value.size() == 0) {
                hrono_events.erase(key);
            }
        }
        return count;
    }
    template <class Function>
    vector<string> FindIf(Function predicate) const {
        vector<string> result;

        for (const auto& [key, value] : hrono_events) {
            for (const auto& event : value) {
                if (predicate(key, event)) {
                    result.push_back(DataToString(key) + " " + event);
                }
            }
        }
        return result;
    }


    string Last(const Date& date) const;
};
