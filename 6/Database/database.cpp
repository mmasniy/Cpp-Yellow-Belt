#include "database.h"

string DataToString(const Date& date) {
    return to_string(date.GetYear()) + "-" + to_string(date.GetMonth()) + "-" + to_string(date.GetDay());
}

void Database::Add(const Date& date, const string& event) {
    if (events.at(date).count(event) == 0) {
        events[date].insert(event);
        hrono_events[date].push_back(event);
    }
}

vector<string> Database::FindIf(const function<bool(const Date& date, const string& event)>& predicate) const {
    vector<string> result;

    for(const auto& [key, events_] : hrono_events) {
        auto it = stable_partition(events_.begin(), events_.end(), predicate);
        result.insert(result.end(), events_.begin(), it);
    }
    return result;
}

int Database::RemoveIf(const function<bool(const Date& date, const string& event)>& predicate) {
    int count = 0;
    for (auto& [key, value] : hrono_events) {
        stable_partition(value.begin(), value.end(), predicate);
    }
    return count;
}

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
        auto point = upper_bound(hrono_events.begin(), hrono_events.end(), date);
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
