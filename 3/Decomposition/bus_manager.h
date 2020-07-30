#pragma once
#include <string>
#include "responses.h"

using namespace std;

class BusManager {
    map<string, vector<string>> buses_to_stops, stops_to_buses; // остановки для автобусов, автобусы для остановки!
public:
    void PrintMaps() const;
    void AddBus(const string& bus, const vector<string>& stops);
    BusesForStopResponse GetBusesForStop(const string& stop) const;
    StopsForBusResponse GetStopsForBus(const string& bus) const;
    AllBusesResponse GetAllBuses() const;
};

