#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

bool operator < (const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int  FindMaxRepetitionCount(const vector<Region>& regions) {
    map<Region, int> count_region;
    int result = 0;

    if (regions.size() == 0) {
        return result;
    }
    for (const auto& region : regions) {
        result = max(result, ++count_region[region]);
    }
    return result;
}


//tuple<const basic_string<char> &, const basic_string<char> &, const map<Lang, basic_string<char>> &, const long long int &>
//GetStruct(const Region& region) {
//    return tie(region.std_name, region.parent_std_name, region.names, region.population);
//}
//
//int  FindMaxRepetitionCount(const vector<Region>& regions) {
//    vector<int> count_region;
//    int count = 0;
//
//    for (size_t i = 0; i < regions.size(); ++i) {
//        count = 0;
//        for (size_t j = 0; j < regions.size(); ++j) {
//            if (GetStruct(regions[i]) == GetStruct(regions[j])) {
//                count++;
//            }
//        }
//        count_region.push_back(count);
//    }
//
//    int result = *max_element(count_region.begin(), count_region.end());
//    return static_cast<int>(result);
//}

int main() {
    cout << FindMaxRepetitionCount({
       {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
               89
       }, {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
               89
       },
       }) << endl;

    cout << FindMaxRepetitionCount({
       {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
               89
       }, {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Moscow",
               "Toulouse",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
       }, {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               31
       },
       }) << endl;

    return 0;
}


//
// Created by mmasniy on 10.07.2020.
//

