#include "node.h"

bool EventComparisonNode::Evaluate(const Date &_date, const string &_event) const {
    return ComporisionTwoNodes(value, _event, cmp);
}

bool DateComparisonNode::Evaluate(const Date &_date, const string &_event) const {
    return ComporisionTwoNodes(date, _date, cmp);
}

bool LogicalOperationNode::Evaluate (const Date& date, const string& event) const {
    if (logical_operation == LogicalOperation::And) {
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    }
    else if (logical_operation == LogicalOperation::Or) {
        return left->Evaluate(date, event) || right->Evaluate(date, event);
    }
    else {
        throw(invalid_argument(""));
    }
}

