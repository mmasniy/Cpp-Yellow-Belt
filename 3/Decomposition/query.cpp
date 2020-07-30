#include "query.h"

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

//
// Created by mmasniy on 18.07.2020.
//

