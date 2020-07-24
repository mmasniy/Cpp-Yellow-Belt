#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
protected:
    const string name_;

public:
    Human(const string& name): name_(name) {
    }

    ~Human() = default;

    virtual const string& type() const = 0;

    const string& name() const {
        return name_;
    }

    virtual void Walk(const string& destination) const {
        cout << type() <<": " << name_ << " walks to: " << destination << endl;
    };
};

class Student : public Human {
public:

    Student(const string& name_, const string& favouriteSong) : Human(name_), FavouriteSong(favouriteSong){
    }

    void Learn() const {
        cout << "Student: " << name_ << " learns" << endl;
    }

    void SingSong() const {
        cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    const string& type() const override {
        return type_;
    };

public:
    const string FavouriteSong;

private:
    inline static const string type_ = "Student";
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human(name), Subject(subject) {
    }

    void Teach() const {
        cout << "Teacher: " << name_ << " teaches: " << Subject << endl;
    }

    const string& type() const override {
        return type_;
    }

public:
    const string Subject;

private:
    inline static const string type_ = "Teacher";
};


class Policeman : public Human {
public:
    Policeman(const string& name_) : Human(name_) {
    }

    void Check(const Human& h) const {
        cout << type_ << ": " << name_ << " checks " << h.type() << ". " << h.type() <<"'s name is: " << h.name() << endl;
    }

    const string& type() const override {
        return type_;
    }

private:
    inline static const string type_ = "Policeman";
};

void VisitPlaces(const Human& human, const vector<string>& places) {
    for (const auto& p : places) {
        human.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}

