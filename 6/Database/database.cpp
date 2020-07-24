#include "database.h"

void Database::Add(const Date& date, const string& event) {
    events[date].insert(event);
}

template <class Func>
int Database::FindIf(Func predicate) {

}

template <class Func>
int Database::RemoveIf(Func predicate) {
    int count = 0;
    for (auto& [key, value] : events) {
        for (auto& event : value) {
            if (predicate(key, event)) {
                value.erase(event);
                count++;
            }
        }
    }
    return count;
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
