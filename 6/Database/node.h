#pragma once
#include "date.h"

class Node {
    virtual function<bool (Date, string)> Evaluate (Date date, string event) = 0;
};

class EmptyNode : public Node{

};

class DateComparisonNode : public Node {

};

class EventComparisonNode : public Node {

};

class LogicalOperationNode : public Node {

};