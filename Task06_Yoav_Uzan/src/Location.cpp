#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Location
{
	float _longitude;
	float _latitude;
	Location(const std::string& input) {
		std::vector<std::string> result;
		std::string token;
		std::istringstream tokenStream(input);
		std::string delimiter = "-";

		while (std::getline(tokenStream, token, delimiter.at(0))) {
			result.push_back(token);
		}
		if (result.size() >= 2) {
			_longitude = std::stof(result[0]);
			_latitude = std::stof(result[1]);
		}

	}
	bool operator  < (const Location& rhs) const
	{
		return _longitude < rhs._longitude && _latitude < rhs._latitude;
	}
	bool operator  > (const Location& rhs) const
	{
		return _longitude > rhs._longitude && _latitude > rhs._latitude;
	}
	bool operator == (const Location & rhs) const
	{
		return _longitude == rhs._longitude && _latitude == rhs._latitude;
	}
	bool operator != (const Location & rhs) const
	{
		return _longitude != rhs._longitude && _latitude != rhs._latitude;
	}
	bool operator  <= (const Location & rhs) const
	{
		return _longitude <= rhs._longitude && _latitude <= rhs._latitude;
	}
	bool operator  >= (const Location & rhs) const
	{
		return _longitude >= rhs._longitude && _latitude >= rhs._latitude;
	}
	friend std::ostream& operator<<(std::ostream& os, const Location& obj)
	{
		os << obj._longitude << "-" << obj._latitude;
		return os;
	}

};