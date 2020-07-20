#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

//My work option

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    vector<T> result;
    auto position = find_if(begin(elements), end(elements), [&border](T t) {
        return t > border;
    });

    if (position == end(elements)) {
        return result;
    }
    else {
        while (position != end(elements)) {
            result.push_back(*position);
            position++;
        }
        return result;
    }
}

//Option to work with coursera

//template <typename T>
//vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
//    auto element = begin(elements);
//
//    while(element != end(elements) && *element <= border) {
//        element++;
//    }
//    return {element, end(elements)};
//}

int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
        cout << x << " ";
    }
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

//
// Created by mmasniy on 18.07.2020.
//

