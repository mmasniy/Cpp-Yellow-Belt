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
    virtual string Name() = 0;

    virtual double Perimeter() = 0;

    virtual double Area() = 0;
};

class Triangle : public Figure {
public:
    Triangle (const string& name_, double a_, double b_, double c_) {
        name = name_;
        a = a_;
        b = b_;
        c = c_;
    }

    string Name() override {
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
    string name;
    double a, b, c;
};

class Rect : public Figure {
public:
    Rect (const string& name_, double width_, double height_) {
        name = name_;
        width = width_;
        height = height_;
    }

    string Name() override {
        return name;
    }

    double Perimeter() override {
        return width * 2 + height * 2;
    }

    double Area() override {
        return width * height;
    }

private:
    string name;
    double width, height;
};

class Circle : public Figure {
public:
    Circle (const string& name_, double radius_) {
        name = name_;
        radius = radius_;
    }

    string Name() override {
        return name;
    }

    double Perimeter() override {
        return 2 * 3.14 * radius;
    }

    double Area() override {
        return 3.14 * radius * radius;
    }

private:
    string name;
    double radius;
};

int main() {
    Triangle a = {"Tric", 3, 4, 5};
    cout << a.Name() << " " << a.Perimeter() << " " << a.Area() << endl;
    Rect r = {"Rect", 10, 20};
    cout << r.Name() << " " << r.Perimeter() << " " << r.Area() << endl;
    Circle c = {"Circle",5 };
    cout << c.Name() << " " << c.Perimeter() << " " << c.Area() << endl;
//    vector<shared_ptr<Figure>> figures;
//    for (string line; getline(cin, line); ) {
//        istringstream is(line);
//
//        string command;
//        is >> command;
//        if (command == "ADD") {
//            // Пропускаем "лишние" ведущие пробелы.
//            // Подробнее об std::ws можно узнать здесь:
//            // https://en.cppreference.com/w/cpp/io/manip/ws
//            is >> ws;
//            figures.push_back(CreateFigure(is));
//        } else if (command == "PRINT") {
//            for (const auto& current_figure : figures) {
//                cout << fixed << setprecision(3)
//                     << current_figure->Name() << " "
//                     << current_figure->Perimeter() << " "
//                     << current_figure->Area() << endl;
//            }
//        }
//    }
    return 0;
}

//
// Created by mmasniy on 23.07.2020.
//

