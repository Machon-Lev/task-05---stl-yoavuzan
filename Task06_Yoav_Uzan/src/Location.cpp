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
		if (result.size() >= 2) 
		{
			_longitude = std::stof(result[0]);
			_latitude = std::stof(result[1]);
		}
		else 
		{
			throw std::runtime_error("There is a problem with The data.");
		}

	}
	Location(const Location& rhs) {
		_longitude = rhs._longitude;
		_latitude = rhs._latitude;
	}
	Location& operator=(const Location& other) {
		if (this != &other) {
			_longitude = other._longitude;
			_latitude = other._latitude;
		}
		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Location& obj)
	{
		os << obj._longitude << "-" << obj._latitude;
		return os;
	}

};