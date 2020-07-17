#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

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

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
        int GCD = gcd(new_numerator, new_denominator);

        if (new_denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        if (new_denominator < 0 ^ new_numerator < 0) {
            new_denominator = abs(new_denominator);
            new_numerator = abs(new_numerator) * -1;
        }
        else {
            new_numerator = abs(new_numerator);
            new_denominator = abs(new_denominator);
        }
        numerator = new_numerator / GCD;
        denominator = new_denominator / GCD;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator; // числитель
    int denominator; // знаменатель
};

bool operator !=(const Rational& lhs, const Rational& rhs) {
    int lcm_numerator = lcm(lhs.Numerator(), rhs.Numerator());
    int lcm_denominator =  lcm(lhs.Denominator(), rhs.Denominator());

    return !((lhs.Numerator() * lcm_numerator == rhs.Numerator() * lcm_numerator)
             && (lhs.Denominator() * lcm_denominator == rhs.Denominator() * lcm_denominator));
}

bool operator ==(const Rational& lhs, const Rational& rhs) {
    int lcm_numerator = lcm(lhs.Numerator(), rhs.Numerator());
    int lcm_denominator =  lcm(lhs.Denominator(), rhs.Denominator());

    return (lhs.Numerator() * lcm_numerator == rhs.Numerator() * lcm_numerator)
           && (lhs.Denominator() * lcm_denominator == rhs.Denominator() * lcm_denominator);
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& rational) {
    int new_numerator, new_denominator;;

    if (stream) {
        stream >> new_numerator;
    }
    else
        return stream;
    stream.ignore(1);
    if (stream) {
        stream >> new_denominator;
    }
    else
        return stream;
    rational = {new_numerator, new_denominator};
    return stream;
}

bool operator >(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() / (double)lhs.Denominator()) > (rhs.Numerator() / (double)rhs.Denominator());
}

bool operator <(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() / (double)lhs.Denominator()) < (rhs.Numerator() / (double)rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0)
        throw domain_error("Devision by zero");
    return Rational{lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational{lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int lcm_denominator = lcm(lhs.Denominator(), rhs.Denominator());
    int l_multiplier = lcm_denominator / lhs.Denominator();
    int r_multiplier = lcm_denominator / rhs.Denominator();

    return Rational{lhs.Numerator() * l_multiplier - rhs.Numerator()
                                                     * r_multiplier, lcm_denominator};
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int lcm_denominator = lcm(lhs.Denominator(), rhs.Denominator());
    int l_multiplier = lcm_denominator / lhs.Denominator();
    int r_multiplier = lcm_denominator / rhs.Denominator();

    return Rational{lhs.Numerator() * l_multiplier + rhs.Numerator()
                                                     * r_multiplier, lcm_denominator};
}

void TestDefaultConstructor() {
    {
//        Rational test = {12, 6};
//        Rational test2 = {12, 6};
        Rational test1{0, 1};//test - test2;
        Rational t;

        AssertEqual(test1, t, "numerator = 0, denominator = 1");
        AssertEqual(0, t.Numerator(), "numerator = 0, denominator = 1");
        AssertEqual(1, t.Denominator(), "numerator = 0, denominator = 1");

        Rational r;
        AssertEqual(r.Numerator(), 0, "test_default");
        AssertEqual(r.Denominator(), 1, "test_default");
    }
    {
        Rational r(0, 3);
        AssertEqual(r.Numerator(), 0, "Numerator test_default_5");
        AssertEqual(r.Denominator(), 1, "Denominator test_default_5");
    }
}

void TestFractionReduction() {
    {
        Rational test = {12, 6};
        Rational valid = {2, 1};

        AssertEqual(test, valid, "numerator = 1, denominator = 1");
        AssertEqual(test.Numerator(), 2, "numerator = 2");
        AssertEqual(test.Denominator(), 1, "denominator = 1");
    }
    {
        Rational test = {12, 16};
        Rational valid = {12, 16};

        AssertEqual(test, valid, "numerator = 3, denominator = 4");
        AssertEqual(test.Numerator(), 3, "numerator = 3");
        AssertEqual(test.Denominator(), 4, "denominator = 4");
    }
    {
        Rational r(2,4);
        AssertEqual(r.Numerator(), 1, "Numerator = 1");
        AssertEqual(r.Denominator(), 2, "Denominator = 2");

        Rational r1(21,12);
        AssertEqual(r1.Numerator(), 7, "Numerator = 7");
        AssertEqual(r1.Denominator(), 4, "Denominator = 4");
    }
}

void TestPositiveAndNegativeValue() {
    {
        Rational test = {-12, 6};
        Rational valid = {-12, 6};
        AssertEqual(test, valid, "numerator = -3, denominator = 1");
        AssertEqual(test.Numerator(), -2, "numerator = -2");
        AssertEqual(test.Denominator(), 1, "denominator = 1");
    }
    {
        Rational test = {-12, -6};
        Rational valid = {12, 6};
        AssertEqual(test, valid, "Negative value");
        AssertEqual(test.Numerator(), 2, "Positive value, numerator = 2");
        AssertEqual(test.Denominator(), 1, "Positive value, denominator = 1");
    }
    {
        Rational r(-3, 2);
        AssertEqual(r.Numerator(), -3, "Numerator test_negative");
        AssertEqual(r.Denominator(), 2, "Denominator test_negative");

        Rational  r1(55,-2);
        AssertEqual(r1.Numerator(), -55, "Numerator test_negative");
        AssertEqual(r1.Denominator(), 2, "Denominator test_negative");
    }
    {
        Rational r(99, 8);
        AssertEqual(r.Numerator(), 99, "Numerator test_positive");
        AssertEqual(r.Denominator(), 8, "Denominator test_positive");
    }
    {

        Rational r(-99, -8);
        AssertEqual(r.Numerator(), 99, "Numerator test_positive");
        AssertEqual(r.Denominator(), 8, "Denominator test_positive");
    }
}

void TestByZero() {
    {
        Rational valid = {0, 1};
        Rational test1;
        AssertEqual(test1, valid, "numerator = 0, denominator = 1");
        AssertEqual(test1.Numerator(), 0, "Numerator = 0, denominator = 1");
        AssertEqual(test1.Denominator(), 1, "numerator = 0, Denominator = 1");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestFractionReduction, "TestFractionReduction");
    runner.RunTest(TestPositiveAndNegativeValue, "TestPositiveAndNegativeValue");
    runner.RunTest(TestByZero, "TestByZero");
    return 0;
}

/*
Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.

При конструировании объекта класса Rational с параметрами
p и q должно выполняться сокращение дроби p/q.

Если дробь p/q отрицательная, то объект Rational(p, q)
должен иметь отрицательный числитель и положительный знаменатель.

Если дробь p/q положительная, то объект Rational(p, q)
должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).

 Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
 */

//
// Created by Maksim Masniy on 7/17/20.
//
