#pragma once
#include <memory>
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

template<class T>
bool ComporisionTwoNodes(T node1, T node2, Comparison comp) {
    switch (comp) {
        case Less:
            return node1 > node2;
        case LessOrEqual:
            return node1 >= node2;
        case Greater:
            return node1 < node2;
        case GreaterOrEqual:
            return node1 <= node2;
        case Equal:
            return node1 == node2;
        case NotEqual:
            return node1 != node2;
    }
}

class Node {
public:
    virtual ~Node() = default;
    virtual bool Evaluate (const Date& _date, const string& _event) const = 0;
};

class EmptyNode : public Node{
public:
    bool Evaluate (const Date& _date, const string& _event) const override {
        return true;
    }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp_, const Date& date_)
    : cmp(cmp_), date(date_){
    }

    bool Evaluate (const Date& _date, const string& _event) const override;
private:
    const Comparison cmp;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp_, const string& value_)
    : cmp(cmp_), value(value_){
    }
    bool Evaluate (const Date& _date, const string& _event) const override;

private:
    const Comparison cmp;
    const string value;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation _log_operation,
                         shared_ptr <Node> _left, shared_ptr <Node> _rigth)
            : logical_operation(_log_operation), left(_left), right(_rigth){
    }

    bool Evaluate (const Date& date, const string& event) const override;

private:
    const LogicalOperation logical_operation;
    shared_ptr <Node> left, right;
};