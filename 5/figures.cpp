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
    virtual string Name() const = 0;

    virtual double Perimeter() = 0;

    virtual double Area() = 0;

    virtual ~Figure() = default;

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

    double Perimeter() override {
        return a + b + c;
    }

    double Area() override {
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

    double Perimeter() override {
        return width * 2 + height * 2;
    }

    double Area() override {
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

    double Perimeter() override {
        return 2 * 3.14 * radius;
    }

    double Area() override {
        return 3.14 * radius * radius;
    }

private:
    const double radius;
};

shared_ptr<Figure> CreateFigure(istringstream& parameter) {
    string figure_type;
    parameter >> figure_type;
    if (figure_type == "RECT") {
        double width_, height_;
        parameter >> width_ >> height_;
        return make_shared<Rect>(width_, height_);
    }
    else if (figure_type == "TRIANGLE") {
        double a_, b_, c_;
        parameter >> a_ >> b_ >> c_;
        return make_shared<Triangle>(a_, b_, c_);
    }
    else if (figure_type == "CIRCLE") {
        double radius_;
        parameter >> radius_;
        return make_shared<Circle>(radius_);
    }
    return 0;
}

int main() {
//    Triangle a = {"Tric", 3, 4, 5};
//    cout << a.Name() << " " << a.Perimeter() << " " << a.Area() << endl;
//    Rect r = {"Rect", 10, 20};
//    cout << r.Name() << " " << r.Perimeter() << " " << r.Area() << endl;
//    Circle c = {"Circle",5 };
//    cout << c.Name() << " " << c.Perimeter() << " " << c.Area() << endl;
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
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

