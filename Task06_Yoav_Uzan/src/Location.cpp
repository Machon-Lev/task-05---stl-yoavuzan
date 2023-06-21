#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

struct Location
{
    double _longitude; // Longitude value of the location
    double _latitude;  // Latitude value of the location

    // Constructor that takes a string input in the format "longitude-latitude"
    Location(const std::string& input)
    {
        std::vector<std::string> result;
        std::string token;
        std::istringstream tokenStream(input);
        std::string delimiter = "-";

        // Splitting the input string by the delimiter and storing the tokens in a vector
        while (std::getline(tokenStream, token, delimiter.at(0)))
        {
            result.push_back(token);
        }

        if (result.size() >= 2)
        {
            _longitude = std::stod(result[0]); // Converting the longitude token to a double
            _latitude = std::stod(result[1]);  // Converting the latitude token to a double
        }
        else
        {
            throw std::runtime_error("There is a problem with the data.");
        }
    }

    // Copy constructor
    Location(const Location& rhs)
    {
        _longitude = rhs._longitude;
        _latitude = rhs._latitude;
    }

    // Assignment operator
    Location& operator=(const Location& other)
    {
        if (this != &other)
        {
            _longitude = other._longitude;
            _latitude = other._latitude;
        }
        return *this;
    }

    // Overloaded << operator to output a Location object in the format "longitude-latitude"
    friend std::ostream& operator<<(std::ostream& os, const Location& obj)
    {
        os << obj._longitude << "-" << obj._latitude;
        return os;
    }
};
