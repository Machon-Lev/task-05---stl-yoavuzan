#pragma once
#include "Location.cpp"
#include <functional>
#include <iostream>
struct SortByMap {
    std::function<float(const Location&, const Location&)> _calcDistance;
    Location _centeralCityLocation;

    SortByMap(std::function<float(const Location&, const Location&)> func, const Location& param)
        : _calcDistance(std::move(func)), _centeralCityLocation(param) {}

    bool operator()(const std::pair<const std::string, Location>& a, const std::pair<const std::string, Location>& b) const {
        return _calcDistance(a.second, _centeralCityLocation) < _calcDistance(b.second, _centeralCityLocation);
    }
};