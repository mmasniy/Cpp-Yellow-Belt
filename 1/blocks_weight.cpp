#include <iostream>
#include <vector>
#include <map>

using namespace std;

uint64_t weight_block(const vector<int>& parameters, int density) {
    uint64_t weight_block = 1;

    for (const int& p : parameters) {
        weight_block *= static_cast<uint64_t>(p);
    }
    return weight_block * density;
}

int main() {
    int n, r, buffer;
    uint64_t sum_weight = 0;
    cin >> n >> r;
    for (; n > 0; --n) {
        vector<int> blocks;
        for (int i = 0; i < 3; ++i) {
            cin >> buffer;
            blocks.push_back(buffer);
        }
        sum_weight += weight_block(blocks, r);
    }
    cout << sum_weight << endl;
}

//
// Created by mmasniy on 09.07.2020.
//
