#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string type, input;
    is >> type;
    if (type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus >> q.stop;
        q.stops.resize(stoi(q.stop));
        for (auto& stop : q.stops) {
            is >> stop;
        }
    }
    else if (type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    }
    else if (type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    }
    else if (type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (!r.buses.empty()) {
        bool first = true;
        for (const auto& bus : r.buses) {
            if (!first) {
                os << " ";
            }
            first = false;
            os << bus;
        }
    }
    else {
        os << "No stop";
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<string> stops_for_bus;
    map<string, vector<string>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_bus.empty()) {
        os << "No bus";
    }
    else {
        bool first = true;
        for (const auto& stop : r.stops_for_bus) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Stop " << stop << ": ";
            if (r.stops_for_buses.at(stop).size() == 1) {
                os << "no interchange";
            }
            else {
                for (const auto& other_bus : r.stops_for_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    }
    else {
        bool first = true;
        for (const auto& bus_item : r.buses_to_stops) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Bus " << bus_item.first << ": ";
            for (const auto& stop : bus_item.second) {
                os << stop << " ";
            }
        }
    }
    return os;
}

class BusManager {
    map<string, vector<string>> buses_to_stops, stops_to_buses; // остановки для автобусов, автобусы для остановки!
public:
//    void PrintMaps() const {
//        cout << "Buses for stops" << endl;
//        for (const auto& bus_item : buses_to_stops) {
//            cout << bus_item.first << ": ";
//            for (const auto& stop : bus_item.second) {
//                cout << stop << " ";
//            }
//            cout << endl;
//        }
//        cout << "\n\nStops for buses" << endl;
//        for (const auto& bus_item : stops_to_buses) {
//            cout << bus_item.first << ": ";
//            for (const auto& stop : bus_item.second) {
//                cout << stop << " ";
//            }
//            cout << endl;
//        }
//    }
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const auto& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) != 0) {
            return {stops_to_buses.at(stop)};
        }
        return {};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) != 0) {
            return {bus, buses_to_stops.at(bus), stops_to_buses};
        }
        return {};
    }

    AllBusesResponse GetAllBuses() const {
        return {buses_to_stops};
    }
};

//void TestAddBus(BusManager bm, Query q) {
//    {
//        assert(bm.AddBus(q.bus, q.stops) = {
//            {"32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"}},
//            {{"Tolstopaltsevo", "32"}, {"Marushkino", "32"}, {"Vnukovo", "32"}}
//        }
//        );
//    }
//}

//void TestBusesForStop() {
//
//}
//
//void TestStopsForBus() {
//
//}
//
//void TestAllBuses() {

//}

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
//                bm.PrintMaps();
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}

//int main() {
//    int q;
//    cin >> q;
//
//    map<string, vector<string>> buses_to_stops, stops_to_buses;
//
//    for (int i = 0; i < q; ++i) {
//        string operation_code;
//        cin >> operation_code;
//
//        if (operation_code == "NEW_BUS") {
//
//            string bus;
//            cin >> bus;
//            int stop_count;
//            cin >> stop_count;
//            vector<string>& stops = buses_to_stops[bus];
//            stops.resize(stop_count);
//            for (string& stop : stops) {
//                cin >> stop;
//                stops_to_buses[stop].push_back(bus);
//            }
//
//        } else if (operation_code == "BUSES_FOR_STOP") {
//
//            string stop;
//            cin >> stop;
//            if (stops_to_buses.count(stop) == 0) {
//                cout << "No stop" << endl;
//            } else {
//                for (const string& bus : stops_to_buses[stop]) {
//                    cout << bus << " ";
//                }
//                cout << endl;
//            }
//
//        } else if (operation_code == "STOPS_FOR_BUS") {
//
//            string bus;
//            cin >> bus;
//            if (buses_to_stops.count(bus) == 0) {
//                cout << "No bus" << endl;
//            } else {
//                for (const string& stop : buses_to_stops[bus]) {
//                    cout << "Stop " << stop << ": ";
//                    if (stops_to_buses[stop].size() == 1) {
//                        cout << "no interchange";
//                    } else {
//                        for (const string& other_bus : stops_to_buses[stop]) {
//                            if (bus != other_bus) {
//                                cout << other_bus << " ";
//                            }
//                        }
//                    }
//                    cout << endl;
//                }
//            }
//
//        } else if (operation_code == "ALL_BUSES") {
//
//            if (buses_to_stops.empty()) {
//                cout << "No buses" << endl;
//            } else {
//                for (const auto& bus_item : buses_to_stops) {
//                    cout << "Bus " << bus_item.first << ": ";
//                    for (const string& stop : bus_item.second) {
//                        cout << stop << " ";
//                    }
//                    cout << endl;
//                }
//            }
//
//        }
//    }
//
//    return 0;
//}

//
// Created by mmasniy on 15.07.2020.
//

