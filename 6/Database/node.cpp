
#include "node.h"

EventComparisonNode::EventComparisonNode(const Comparison& cmp_, const string& value_): cmp(cmp_), value(value_){
}

bool EventComparisonNode::Evaluate(const Date &_date, const string &_event) const {
    return ComporisionTwoNodes(value, _event, cmp);
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp_, const Date& date_)
        : cmp(cmp_), date(date_){
}

bool DateComparisonNode::Evaluate(const Date &_date, const string &_event) const {
    return ComporisionTwoNodes(date, _date, cmp);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation _log_operation, shared_ptr<Node> _left, shared_ptr<Node> _rigth) :
logical_operation(_log_operation), left(_left), right(_rigth){
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

