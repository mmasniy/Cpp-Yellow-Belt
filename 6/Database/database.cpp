#include "database.h"

string DataToString(const Date& date) {
    stringstream out;
    string result;
    out << setw(4) << setfill('0') << date.GetYear() << "-"
        << setw(2) << setfill('0') << date.GetMonth() << "-"
        << setw(2) << setfill('0') << date.GetDay();
    getline(out, result);
    return result;
}

void Database::Add(const Date& date, const string& event) {
    if (events[date].count(event) == 0) {
        events[date].insert(event);
        hrono_events[date].push_back(event);
    }
}

vector<string> Database::FindIf(function<bool(const Date& date, const string& event)> predicate) const {
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

int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
    int count = 0;

    for (auto& [key, value] : events) {
        for (auto& event : value) {
            if (predicate(key, event)) {
                events.at(key).erase(event);
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
//
//int Database :: RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
//    map<Date, vector<string>> storage_v_copy = hrono_events;
//    int number = 0;
//
//    for (auto item : storage_v_copy) {
//        Date date = item.first;
//        vector<string> &events = item.second;
//
//        auto it = stable_partition(events.begin(), events.end(),
////                            pred(,date, predicate);
//                                   [predicate, date](const string &event) { return !predicate(date, event); });
//
//        number += events.end() - it;
//        events.erase(it, events.end());
//
//        if (events.size() == 0) {
//            hrono_events.erase(item.first);
//            events.erase(item.first);
//        } else {
//            hrono_events[date] = events;
//            events[date] = set<string>(events.begin(), events.end());
//        }
//    }
//    return number;
//}

//int Database :: RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
//    map<Date, vector<string>> storage_v_copy = hrono_events;
//    int number = 0;
//
//    for (auto item : storage_v_copy) {
//        Date date = item.first;
//        vector<string> &events = item.second;
//
//        auto it = stable_partition(events.begin(), events.end(),
//                                   [predicate, date](const string &event) { return !predicate(date, event); });
//
//        number += events.end() - it;
//        events.erase(it, events.end());
//
//        if (events.size() == 0) {
//            hrono_events.erase(item.first);
//            events.erase(date);
//        } else {
//            hrono_events[date] = events;
//            events[date] = set<string>(events.begin(), events.end());
//        }
//    }
//    return number;
//}

void Database::Print(ostream& out) const {
    for (const auto& [key, value] : hrono_events) {
        for (const string& v : value) {
            out << setw(4) << setfill('0') << key.GetYear() << "-"
                 << setw(2) << setfill('0') << key.GetMonth() << "-"
                 << setw(2) << setfill('0') << key.GetDay() << " ";
            out << v << endl;
        }
    }
}


string Database::Last(const Date& date) const {
    if (hrono_events.begin()->first <= date) {
        auto point = hrono_events.upper_bound(date);
        if (point != hrono_events.begin()) {
            --point;
            return {DataToString(point->first) + " " + point->second.back()};
        } else {
            return "No entries";
        }
    }
    else {
        return "No entries";
    }
}
