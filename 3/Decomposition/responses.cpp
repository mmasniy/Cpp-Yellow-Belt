#include "responses.h"

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
//
// Created by mmasniy on 18.07.2020.
//

