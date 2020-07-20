#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin > 1) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        RandomIt range_middle = elements.begin() + (elements.end() - elements.begin()) / 2;

        MergeSort(elements.begin(), range_middle);
        MergeSort(range_middle, elements.end());
        merge(elements.begin(), range_middle, range_middle, elements.end(), range_begin);
    }
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
