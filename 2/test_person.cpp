#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

string GetNameOrLastname(const map<int, string>& data, int year) {
    string buffer;

    for(const auto& [key, value] : data) {
        if (key <= year){
            buffer = value;
        }
    }
    return buffer;
}

class Person {
    map<int, string> names;
    map<int, string> last_n;
public:
    void ChangeFirstName(int year, const string& first_name) {
        if (names.count(year) == 1)
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

void TestIncognito() {
    {
        Person max;
        AssertEqual(max.GetFullName(1999), "Incognito", "Less than a year of birth");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",
                    to_string(4000) + "So much before the birth of the second prophet");
    }
}

void TestGetFirstName() {
    {
        Person max;
        max.ChangeFirstName(2000, "Maks");
        AssertEqual(max.GetFullName(2000), "Maks with unknown last name", "Less than a year of birth");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",to_string(4000) + "So much before the birth of the second prophet");
        AssertEqual(max.GetFullName(4000), "Maks with unknown last name", "RIP");
    }
}

void TestGetLastName() {
    {
        Person max;
        max.ChangeLastName(2000, "Masniy");
        max.ChangeLastName(2010, "Nikolenko");
        max.ChangeLastName(2011, "Masniy");
        AssertEqual(max.GetFullName(2000), "Masniy with unknown first name", "My first last name");
        AssertEqual(max.GetFullName(2010), "Nikolenko with unknown first name", "My second last name");
        AssertEqual(max.GetFullName(2011), "Masniy with unknown first name", "My third last name");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",
                    to_string(4000) + "So much before the birth of the second prophet");
        AssertEqual(max.GetFullName(4000), "Masniy with unknown first name", "RIP");
    }
}

void TestGetFullName() {
    {
        Person max;

        max.ChangeFirstName(2000, "Maks");
        max.ChangeLastName(2000, "Masniy");
        max.ChangeLastName(2010, "Nikolenko");
        max.ChangeLastName(2011, "Masniy");

        AssertEqual(max.GetFullName(1999), "Incognito", "Less than a year of birth");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",
                    to_string(4000) + "So much before the birth of the second prophet");
        AssertEqual(max.GetFullName(2000), "Maks Masniy", "Year when jesus was born");
        AssertEqual(max.GetFullName(2010), "Maks Nikolenko", "Prophet 10 years old");
        AssertEqual(max.GetFullName(2011), "Maks Masniy", "Prophet 11 years old");
    }
}

void TestChangeFirstName() {
    {
        Person max;

        max.ChangeFirstName(2000, "Maks");
        AssertEqual(max.GetFullName(2000), "Maks with unknown last name", "My first last name");
        max.ChangeFirstName(2001, "Petr");
        AssertEqual(max.GetFullName(2010), "Petr with unknown last name", "line 200");
    }
    {
        Person max;

        max.ChangeFirstName(2000, "Maks");
        max.ChangeLastName(2000, "Masniy");
        max.ChangeLastName(2010, "Nikolenko");
        max.ChangeLastName(2011, "Masniy");

        AssertEqual(max.GetFullName(1999), "Incognito", "Less than a year of birth");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",
                    to_string(4000) + "So much before the birth of the second prophet");
        AssertEqual(max.GetFullName(2000), "Maks Masniy", "Year when jesus was born");
        AssertEqual(max.GetFullName(2010), "Maks Nikolenko", "Prophet 10 years old");
        AssertEqual(max.GetFullName(2011), "Maks Masniy", "Prophet 11 years old");
    }
}

void TestChangeLastName() {
    {
        Person max;

        max.ChangeLastName(2000, "Masniy");
        AssertEqual(max.GetFullName(2000), "Masniy with unknown first name", "line 225");
        max.ChangeFirstName(2001, "Petr");
        max.ChangeLastName(2010, "Nikolenko");
        AssertEqual(max.GetFullName(2010), "Petr Nikolenko", "line 228");
    }
    {
        Person max;

        max.ChangeFirstName(2000, "Maks");
        max.ChangeLastName(2000, "Masniy");
        max.ChangeLastName(2010, "Nikolenko");
        max.ChangeLastName(2011, "Masniy");

        AssertEqual(max.GetFullName(1999), "Incognito", "Less than a year of birth");
        AssertEqual(max.GetFullName(0), "Incognito", "Year when jesus was born");
        AssertEqual(max.GetFullName(-2000), "Incognito",
                    to_string(4000) + "So much before the birth of the second prophet");
        AssertEqual(max.GetFullName(2000), "Maks Masniy", "Year when jesus was born");
        AssertEqual(max.GetFullName(2010), "Maks Nikolenko", "Prophet 10 years old");
        AssertEqual(max.GetFullName(2011), "Maks Masniy", "Prophet 11 years old");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestGetFirstName, "TestGetFirstName");
    runner.RunTest(TestGetLastName, "TestGetLastName");
    runner.RunTest(TestGetFullName, "TestGetFullName");
    runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
    runner.RunTest(TestChangeLastName, "TestChangeLastName");

    return 0;
}

//
// Created by mmasniy on 17.07.2020.
//

