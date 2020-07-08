#include <iostream>
#include <vector>

using namespace std;

void get_temperature_all_days(vector<int>& temperature) {
    for (int& t : temperature) {
        cin >> t;
    }
}

int64_t get_average_temperature(const vector<int>& temperature) {
    int64_t sum = 0;

    for (auto t : temperature)
        sum += t;

    return sum / static_cast<int64_t>(temperature.size());
}

void print_day_more_average_temp(const vector<int>& temperature) {
    int day_more_AT = 0;
    int64_t aver_temp = get_average_temperature(temperature);

    for (const auto& t : temperature) {
        if (t > aver_temp)
            day_more_AT++;
    }
    cout << day_more_AT << endl;
    for (size_t i = 0; i < temperature.size(); ++i) {
        if (static_cast<int64_t>(temperature[i]) > aver_temp)
            cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> temperature(n);

    get_temperature_all_days(temperature);
    print_day_more_average_temp(temperature);
    return 0;
}
//
// Created by mmasniy on 08.07.2020.
//
