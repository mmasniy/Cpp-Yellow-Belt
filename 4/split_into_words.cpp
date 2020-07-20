#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto start_word = begin(s);
    while (1) {
        auto it = find(start_word, end(s), ' ');
        result.emplace_back(string(start_word, it));
        if (it == end(s)) {
            break;
        }
        else {
            start_word = ++it;
        }
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}

