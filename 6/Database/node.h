#pragma once
#include "date.h"

enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate (Date date, string event) = 0;
};

class EmptyNode : public Node{
public:
    bool Evaluate (Date date, string event) override {
        return true;
    }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp_, const Date& date_)
    : cmp(cmp_), date(date_){
    }

private:
    const Comparison cmp;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp_, const string& value_)
    : cmp(cmp_), value(value_){
    }

private:
    const Comparison cmp;
    const string value;
};

class LogicalOperationNode : public Node {
public:

private:
    const LogicalOperation logical_operation;

};