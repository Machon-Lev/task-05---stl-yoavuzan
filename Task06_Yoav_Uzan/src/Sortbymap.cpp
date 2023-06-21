#pragma once
#include "Location.cpp"
#include <functional>
#include <iostream>

/**
 brief Comparator struct used for sorting a map by distance from a central location.
 */
struct SortByMap {
    std::function<double(const Location&, const Location&)> _calcDistance;  // Function pointer for distance calculation
    Location _centeralCityLocation;  // Central location used for distance comparison

    /**
     brief Constructs a SortByMap object with the given distance calculation function and central location.
     param func The function used to calculate the distance between two locations.
     param param The central location used as a reference for distance comparison.
     */
    SortByMap(std::function<double(const Location&, const Location&)> func, const Location& param)
        : _calcDistance(std::move(func)), _centeralCityLocation(param) {}

    /**
     brief Overloaded function call operator used for comparing two pairs of string and Location.
     param a The first pair to compare.
     param b The second pair to compare.
     return True if the distance from the central location to 'a' is less than the distance to 'b', false otherwise.
     */
    bool operator()(const std::pair<const std::string, Location>& a, const std::pair<const std::string, Location>& b) const {
        return _calcDistance(a.second, _centeralCityLocation) < _calcDistance(b.second, _centeralCityLocation);
    }
};
