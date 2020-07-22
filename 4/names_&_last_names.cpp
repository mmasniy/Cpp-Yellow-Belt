#include <iostream>
#include <string>
#include <map>

using namespace std;

string GetNameOrLastname(const map<int, string>& data, int year) {
    string buffer;
    auto iter = data.upper_bound(year);
    if (iter != data.begin()) {
        buffer = (--iter)->second;
    }
    return buffer;
}

class Person {
    map<int, string> names;
    map<int, string> last_n;
public:
    void ChangeFirstName(int year, const string& first_name) {
        names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_n[year] = last_name;
    }
    string GetFullName(int year) {
        string name = GetNameOrLastname(names, year);
        string last_name = GetNameOrLastname(last_n, year);

        if (!name.empty() && last_name.empty()) {
            return name + " with unknown last name";
        }
        else if (name.empty() && !last_name.empty()) {
            return last_name + " with unknown first name";
        }
        else if (!name.empty() && !last_name.empty()) {
            return name + " " + last_name;
        }
        else {
            return "Incognito";
        }
    }
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    return 0;
}
