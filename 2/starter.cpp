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

