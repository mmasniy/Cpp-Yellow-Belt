#include <iostream>
#include <deque>
#include <string>
#include <vector>

using namespace std;

int main() {
    deque<string> expression;
    int first_num;
    bool prev = true;
    int iter;

    cin >> first_num;
    expression.push_back(to_string(first_num));
    for(cin >> iter; iter > 0; --iter) {
        vector<string> operation(2);
        cin >> operation[0] >> operation[1];
        if (prev == false && (operation[0] == "*" || operation[0] == "/")) {
            expression.push_front("(");
            expression.emplace_back(")");
        }
        (operation[0] == "*" || operation[0] == "/") ? prev = true : prev = false;
        expression.emplace_back(" ");
        expression.push_back(operation[0]);
        expression.emplace_back(" ");
        expression.push_back(operation[1]);
    }
    for (const string& e : expression) {
        cout << e;
    }
    cout << endl;
    return 0;
}
