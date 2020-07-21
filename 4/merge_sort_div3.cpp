#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin > 1) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        vector<typename RandomIt::value_type> buffer;

        RandomIt range_middle1 = elements.begin() + ((elements.end() - elements.begin()) / 3);
        RandomIt range_middle2 = range_middle1 + ((elements.end() - elements.begin()) / 3);

        MergeSort(elements.begin(), range_middle1);
        MergeSort(range_middle1, range_middle2);
        MergeSort(range_middle2, elements.end());

        merge(elements.begin(), range_middle1, range_middle1, range_middle2, back_inserter(buffer));
        merge(buffer.begin(), buffer.end(), range_middle2, elements.end(), range_begin);
    }
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

