#include <iostream>
#include <algorithm>
#include "sum_reverse_sort.h"

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s){
    char tmp;

    if (s.size() > 1) {
        for (int i = 0; i <= (int)(s.size() / 2) - 1; ++i) {
            tmp = s[i];
            s[i] = s[s.size() - i - 1];
            s[s.size() - i - 1] = tmp;
        }
    }
    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}
//
//int main() {
//    vector<int> nums = {9, 1, 5, 3, 4, 5, 8};
//    cout << Sum(13, 12) << endl;
//    cout << Reverse("CLion") << endl;
//    Sort(nums);
//    for(const auto& i : nums) {
//        cout << i << " ";
//    }
//    return 0;
//}

//
// Created by Maksim Masniy on 7/17/20.
//

