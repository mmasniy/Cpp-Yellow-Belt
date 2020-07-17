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

bool IsPalindrom(const string& str) {
    if (str.empty())
        return true;
    for (int i = 0, j = (int)str.size() - 1; (i < (int)str.size() / 2); ++i, --j) {
        if (str[i] != str[j])
            return false;
    }
    return true;
}

void Test_IsPolindrom() {
    Assert(IsPalindrom(" "), "0");
    Assert(IsPalindrom("a"), "1");
    Assert(IsPalindrom("aa"), "2");
    Assert(IsPalindrom("aaa"), "3");
    Assert(IsPalindrom("AAsAA"), "4");
    Assert(!IsPalindrom("AAsA1"), "5");
    Assert(!IsPalindrom("AAsAA "), "6");
    Assert(!IsPalindrom(" AAsAA"), "7");
    Assert(!IsPalindrom("AAsaA"), "8");
    Assert(IsPalindrom("AAAA"), "9");
    Assert(IsPalindrom(""), "10");
    Assert(!IsPalindrom("AAbcAA"), "11");
    Assert(!IsPalindrom("bc"), "12");
}

int main() {
    TestRunner runner;
    runner.RunTest(Test_IsPolindrom, "Test_IsPolindrom");
    return 0;
}

//
// Created by Maksim Masniy on 7/17/20.
//

