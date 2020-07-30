#include "database.h"

void Database::Add(const Date& date, const string& event) {
    if (events[date].count(event) == 0) {
        events[date].insert(event);
        hrono_events[date].push_back(event);
    }
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
