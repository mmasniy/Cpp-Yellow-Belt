#pragma once

#include "test_runner.h"
#include "database.h"
#include "condition_parser.h"
#include <sstream>
#include "node.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class AlwaysFalseNode : public Node {
    bool Evaluate(const Date&, const std::string& event) const override {
        return false;
    }
};

string ParseEvent(istream& is);

int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
    istringstream is (str);

    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    ostringstream os;
    for (const auto& entry : entries) {
        os << entry << '\n';  // vector<string> {"Date + event"}
    }
    cout << "Found " << entries.size() << " entries" << endl;
    return os.str();
}

void TestDbAdd() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "holiday");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
    }
    {
        Database db;
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
    }
}

void TestDbFind() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year", DoFind(db, "date == 2017-01-01"), "simple find by date");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas", DoFind(db, "date < 2017-01-31"), "multiple find by date");
        AssertEqual("2017-01-01 new year", DoFind(db, R"(event != "xmas")"), "multiple find by holiday");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year2");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, R"(date == 2017-01-07 OR event == "new year")"),
                    "complex find or");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(date == 2017-01-01 AND event == "new year")"),
                    "complex find and");
        AssertEqual("0", DoFind(db, R"(date == 2017-01-09 AND event == "new year")"),
                    "complex find and, nothing");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "Holiday");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-07 xmas\n1", DoFind(db, "date == 2017-01-07"), "single find by date");
        AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2017-01-07 xmas\n3", DoFind(db, "date < 2017-01-31"), "multiple find by date");
        AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2", DoFind(db, R"(event != "xmas")"), "multiple find by event != xmas ");
        AssertEqual("2017-01-01 Holiday\n2017-01-07 xmas\n2", DoFind(db, R"(event != "new year")"), "multiple find by event != new year");
    }

}

void TestDbLast(){
    Database db;
    db.Add({2017, 1, 1}, "new year");
    db.Add({2017, 1, 7}, "xmas");
    {
        try {
            db.Last({2016, 12, 31});
            Assert(false, "last, found no entries");
        } catch (...){
            Assert(true, "last, found no entries");

        }
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 2});
        AssertEqual("2017-01-01 new year", os.str(), "greater than date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 1});
        AssertEqual("2017-01-01 new year", os.str(), "eq to date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 10});
        AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
    }
}

void TestDbRemoveIf () {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
        AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "new year");
        AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
    }
}

void TestInsertionOrder()
{
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "party");
        db.Add({2017, 1, 7}, "pie");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2017-01-07 party\n2017-01-07 pie\n", out.str(), "Remove by date, left");
    }

}

void TestEmptyNode() {
    {
        EmptyNode en;
        Assert(en.Evaluate(Date{0, 1, 1}, "abc"), "EmptyNode 1");
        Assert(en.Evaluate(Date{2017, 11, 18}, "def"), "EmptyNode 2");
        Assert(en.Evaluate(Date{9999, 12, 31}, "ghi"), "EmptyNode 3");
    }
}
