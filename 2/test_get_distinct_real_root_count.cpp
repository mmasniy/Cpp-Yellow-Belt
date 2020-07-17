#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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

int GetDistinctRealRootCount(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    double D = b * b - 4 * a * c;
    if (D < 0)
        return 0;
    if (D == 0)
        return 1;
    else {
        return 2;
    }
}

void one_num_zero() {
    AssertEqual(GetDistinctRealRootCount(0, 10, 189765432), 1, "1 zero.");
    AssertEqual(GetDistinctRealRootCount(0, 65536, -10), 1, "1 zero.");
    AssertEqual(GetDistinctRealRootCount(1, 0, 1073741824), 0, "2 zero.");
    AssertEqual(GetDistinctRealRootCount(2000000000, 0, -100), 2, "2 zero.");
    AssertEqual(GetDistinctRealRootCount(-20, 100, 0), 2, "3 zero.");
    AssertEqual(GetDistinctRealRootCount(2100200100, -1, 0), 2, "3 zero.");
}

void two_num_zero() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 65536*1024), 0, "1 and 2 zero.");
    AssertEqual(GetDistinctRealRootCount(0, 159726483, 0), 1, "1 and 3 zero.");
    AssertEqual(GetDistinctRealRootCount(100, 0, 0), 1, "2 and 3 zero.");
}

void none_num_zero() {
    AssertEqual(GetDistinctRealRootCount(0.1, 2, 812), 0, "D < 0, b > 0.");
    AssertEqual(GetDistinctRealRootCount(0.1, -2, 812), 0, "D < 0, b < 0.");
    AssertEqual(GetDistinctRealRootCount(5, 16, 12.8), 1, "D = 0, b > 0.");
    AssertEqual(GetDistinctRealRootCount(5, -16, 12.8), 1, "D= 0, b < 0.");
    AssertEqual(GetDistinctRealRootCount(-25, 1, 3), 2, "D > 0, a < 0.");
    AssertEqual(GetDistinctRealRootCount(25, 1, -0.25), 2, "D > 0, c < 0.");
    AssertEqual(GetDistinctRealRootCount(25, 250, 25), 2, "D > 0, a, b, c > 0.");
}

void TestAll(TestRunner& runner) {
    runner.RunTest(one_num_zero, "one_num_zero");
    runner.RunTest(two_num_zero, "two_num_zero");
    runner.RunTest(none_num_zero, "none_num_zero");
}

int main() {
    TestRunner runner;
    TestAll(runner);
    return 0;
}

//
// Created by mmasniy on 17.07.2020.
//
//Тесты с курсеры!
//void TestRootCount() {
//    mt19937 gen;
//    uniform_real_distribution<> unif(-10, 10);
//
//    for (auto i = 0; i < 100; ++i) {
//        const auto a = unif(gen);
//        const auto b = unif(gen);
//        const auto c = unif(gen);
//
//        const auto count = GetDistinctRealRootCount(a, b, c);
//
//        Assert(count >= 0 && count <= 2,
//               "Quadratic equation has only 0, 1 or 2 real roots.");
//    }
//}
//
//void TestOneRoot() {
//    mt19937 gen;
//    uniform_real_distribution<> unif(-10, 10);
//
//    for (auto i = 0; i < 100; ++i) {
//        const auto x_1 = unif(gen);
//
//        const auto p = x_1 + x_1;
//        const auto q = x_1 * x_1;
//
//        const auto count = GetDistinctRealRootCount(1, p, q);
//        stringstream description;
//        description << showpos << "x^2" << p << "x" << q
//                    << " = 0 has 1 real root.";
//
//        AssertEqual(count, 1, description.str());
//    }
//}
//
//void TestNoRoots() {
//    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
//                "x^2+1 = 0 has 0 real roots.");
//    AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
//                "x^2+3x+4 = 0 has 0 real roots.");
//    AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
//                "x^2-2x+10 = 0 has 0 real roots.");
//}
//
//void TestLinearEquation() {
//    AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
//                "2x+1 = 0 has 1 real root.");
//    AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
//                "-x = 0 has 1 real root.");
//    AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
//                "120x - 10 = 0 has 1 real root.");
//}
//
//void TestConstant() {
//    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
//                "c = 0, where c = 1 has 0 real roots.");
//    AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
//                "c = 0, where c = -10 has 0 real roots.");
//    AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
//                "c = 0, where c = 189238910 has 0 real roots.");
//}
//
//int main() {
//    TestRunner runner;
//    runner.RunTest(TestRootCount, "TestRootCount");
//    runner.RunTest(TestOneRoot, "TestOneRoot");
//    runner.RunTest(TestNoRoots, "TestNoRoots");
//    runner.RunTest(TestLinearEquation, "TestLinearEquation");
//    runner.RunTest(TestConstant, "TestConstant");
//    return 0;
//}

