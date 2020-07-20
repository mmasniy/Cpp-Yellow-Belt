#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(const vector<int>& number) {
    bool first = true;
    for (const auto& n : number) {
        if (!first) {
            cout << " ";
        }
        first = false;
        cout << n;
    }
    cout << endl;
}

void PrintPermutations(vector<int>& number) {
    do {
        PrintVector(number);
    }
    while (prev_permutation(begin(number), end(number)));
}

int main() {
    int number;
    cin >> number;
    vector<int> permutation;
    while(number) {
        permutation.push_back(number);
        number--;
    }
    PrintPermutations(permutation);
    return 0;
}
