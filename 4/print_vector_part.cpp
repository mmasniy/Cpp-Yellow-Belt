#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto start = find_if(begin(numbers), end(numbers), [](const int& n) {
        return n < 0;
    });

    while(start != begin(numbers)) {
        start--;
        cout << *start << " ";
    }
}

int main() {
    PrintVectorPart({11, 5, 8, 4, 3, 1, 19, 9});
    return 0;
}
