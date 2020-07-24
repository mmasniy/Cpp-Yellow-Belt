#include "database.h"

void Database::Add(const Date& date, const string& event) {
    events[date].insert(event);
}

bool Database::DeleteEvent(const Date& date, const string& event) {
    if (events.find(date) != events.cend()
        && events[date].count(event) != 0) {
        events[date].erase(event);
        return true;
    }
    return false;
}

int  Database::DeleteDate(const Date& date) {
    int events_count = 0;

    if (events.count(date) != 0) {
        events_count = events[date].size();
    }
    events.erase(date);
    return events_count;
}

void Database::FindIf(const Date& date) const {
    if (events.count(date) != 0) {
        set<string> finded = events.at(date);

        for (const string& f : finded) {
            cout << f << endl;
        }
    }
}

template <class Func>
int RemoveIf(Func predicate) {
}

void Database::Print(ostream& out) const {
    for (const auto& [key, value] : events) {
        for (const string& v : value) {
            out << setw(4) << setfill('0') << key.GetYear() << "-"
                 << setw(2) << setfill('0') << key.GetMonth() << "-"
                 << setw(2) << setfill('0') << key.GetDay() << " ";
            out << v << endl;
        }
    }
}
