#include "bus_manager.h"

void BusManager::PrintMaps() const {
    cout << "Buses for stops" << endl;
    for (const auto& bus_item : buses_to_stops) {
        cout << bus_item.first << ": ";
        for (const auto& stop : bus_item.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
    cout << "\n\nStops for buses" << endl;
    for (const auto& bus_item : stops_to_buses) {
        cout << bus_item.first << ": ";
        for (const auto& stop : bus_item.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}
void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) != 0) {
        return {stops_to_buses.at(stop)};
    }
    return {};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    if (buses_to_stops.count(bus) != 0) {
        return {bus, buses_to_stops.at(bus), stops_to_buses};
    }
    return {};
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {buses_to_stops};
}
//
// Created by mmasniy on 18.07.2020.
//

