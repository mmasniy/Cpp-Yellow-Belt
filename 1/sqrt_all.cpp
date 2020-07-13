#include <iostream>
#include <tuple>
#include <map>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename Digit> Digit Sqr(Digit d);
template <typename Digit> vector<Digit> Sqr(const vector<Digit>& v1);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m1);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p1);

template <typename Digit> Digit operator *(Digit a, Digit b) {
    return a * b;
}

template <typename Digit> Digit Sqr(Digit d) {
    return d * d;
}

template <typename Digit> vector<Digit> Sqr(const vector<Digit>& v1) {
    vector<Digit> result;

    for (const auto& i : v1) {
        result.push_back(Sqr(i));
    }
    return result;
}

template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m1) {
    map<Key, Value> result;
    for(const auto& [key, value] : m1) {
        result[key] = Sqr(value);
    }
    return result;
}

template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p1) { // , const pair<First, Second>& p2
//    First f = p1.first * p2.first;
//    Second s = p1.second * p2.second;
    return make_pair(Sqr(p1.first), Sqr(p1.second));
}
//
//int main() {
//    cout << "Start" << endl;
//    // Пример вызова функции
//    vector<int> v = {1, 2, 3};
//    cout << "vector:";
//    for (int x : Sqr(v)) {
//        cout << " " << x;
//    }
//    cout << endl;
//
//    map<int, pair<int, int>> map_of_pairs = {
//            {4, {2, 2}},
//            {7, {4, 3}}
//    };
//    cout << "map of pairs:" << endl;
//    for (const auto& x : Sqr(map_of_pairs)) {
//        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
//    }
//}

//
// Created by Maksim Masniy on 7/13/20.
//

