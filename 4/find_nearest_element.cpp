#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto rhs = numbers.lower_bound(border);

    if (rhs == numbers.begin()) {
        return rhs;
    }

    auto lhs = prev(rhs);

    if (rhs == numbers.end()) {
        return lhs;
    }
    bool chs = (border - *lhs <= *rhs - border);
    return chs ? lhs : rhs;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}
