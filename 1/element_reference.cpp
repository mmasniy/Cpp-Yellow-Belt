#include <iostream>
#include <exception>
#include <map>
#include <string>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
    if (m.count(k) == 1) {
        return m[k];
    }
    else {
        throw runtime_error("K isn`t exist!\n");
    }
}

int main() {
    map<int, string> m = {{0, "value"}};
    try {
        string &item = GetRefStrict(m, 1);
        item = "newvalue";
        cout << m[0] << endl; // выведет newvalue
    }
    catch (runtime_error &error) {
        cout << error.what();
    }
}

//
// Created by mmasniy on 14.07.2020.
//

