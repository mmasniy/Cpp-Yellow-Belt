#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    Figure(const string& name_) : name(name_){
    }
    virtual ~Figure() = default;

    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;

protected:
    const string name;
};

class Triangle : public Figure {
public:
    Triangle (double a_, double b_, double c_)
    : Figure("TRIANGLE"), a(a_), b(b_), c(c_){
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return a + b + c;
    }

    double Area() const override {
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    const double a, b, c;
};

class Rect : public Figure {
public:
    Rect (double width_, double height_)
    : Figure("RECT"), width(width_), height(height_) {
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return width * 2 + height * 2;
    }

    double Area() const override {
        return width * height;
    }

private:
    const double width, height;
};

class Circle : public Figure {
public:
    Circle (double radius_) : Figure("CIRCLE"), radius(radius_){
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return 2 * 3.14 * radius;
    }

    double Area() const override {
        return 3.14 * radius * radius;
    }

private:
    const double radius;
};

/*
 * алтернатива if/else конструкции
auto create_rect(istringstream& parameter) {
    double width_, height_;
    parameter >> width_ >> height_;
    return make_shared<Rect>(width_, height_);
}

auto create_trig(istringstream& parameter) {
    double a_, b_, c_;
    parameter >> a_ >> b_ >> c_;
    return make_shared<Triangle>(a_, b_, c_);
}

auto create_circ(istringstream& parameter) {
    double radius_;
    parameter >> radius_;
    return make_shared<Circle>(radius_);
}

shared_ptr<Figure> CreateFigure(istringstream& parameter) {
    string figure_type;
    parameter >> figure_type;

    static const map<string, function<shared_ptr<Figure>(istringstream& parameter)>> m{
            {"RECT", create_rect},
            {"TRIANGLE", create_trig},
            {"CIRCLE", create_circ},
    };
    return m.at(figure_type)(parameter);
}
 *
 */

shared_ptr<Figure> CreateFigure(istringstream& parameter) {
    string figure_type;
    parameter >> figure_type;
    if (figure_type == "RECT") {
        double width_, height_;
        parameter >> width_ >> height_;
        return make_shared<Rect>(width_, height_);
    } else if (figure_type == "TRIANGLE") {
        double a_, b_, c_;
        parameter >> a_ >> b_ >> c_;
        return make_shared<Triangle>(a_, b_, c_);
    } else if (figure_type == "CIRCLE") {
        double radius_;
        parameter >> radius_;
        return make_shared<Circle>(radius_);
    }
    return 0;
}


int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}

//
// Created by mmasniy on 23.07.2020.
//

