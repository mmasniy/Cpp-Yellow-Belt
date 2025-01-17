#include <iostream>
#include <string>
#include <vector>

using namespace std;

//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(
//        RandomIt range_begin, RandomIt range_end, string prefix) {
//
//    // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
//    auto left = lower_bound(range_begin, range_end, prefix);
//
//    // Составим строку, которая в рамках буквенных строк является
//    // точной верхней гранью множества строк, начинающихся с prefix
//    string upper_bound = prefix;
//    ++upper_bound[upper_bound.size() - 1];
//
//    // Первое встреченное слово, не меньшее upper_bound,
//    // обязательно является концом полуинтервала
//    auto right = lower_bound(range_begin, range_end, upper_bound);
//
//    return {left, right};
//}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    size_t size = prefix.size();
    return equal_range(range_begin, range_end, prefix,[&size](const string& s1, const string& s2) {
        return s1.substr(0, size) < s2.substr(0, size);
    });
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
         (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
         (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}


