#include <functional>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include "Location.cpp"
#include <fstream>
using namespace std;
std::string PATH_TO_FILE = "C:\\Users\\becky\\Source\\Repos\\Task06_Yoav_Uzan\\Task06_Yoav_Uzan\\resources\\data.txt";
float L2( const Location& loc1, const Location& loc2)
{
	return sqrt(pow(loc1._latitude - loc2._latitude, 2) + pow(loc1._longitude - loc2._longitude, 2));
}
float L1(const Location& loc1, const Location& loc2)
{
	return abs(loc1._latitude - loc2._latitude) + abs(loc1._longitude - loc2._longitude);
}
float Linf(const Location& loc1, const Location& loc2)
{
	return max(abs(loc1._latitude - loc2._latitude), abs(loc1._longitude - loc2._longitude));
}

int main() {
	std::multimap<std::string, Location > myMap;
	//read in the data from the file data.txt and store it in the map
    std::ifstream inputFile(PATH_TO_FILE);  

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line1, line2;
    while (std::getline(inputFile, line1)) {
        std::getline(inputFile, line2);
        
        myMap.insert({ line1, {Location(line2)} });
    }

    int count = 0;
    for (auto it = myMap.begin(); it != myMap.end() && count < 10; ++it, ++count) {
        std::cout << "City: " << it->first << ", Longitude: " << it->second._longitude << ", Latitude: " << it->second._latitude << std::endl;
    }
    inputFile.close();

    // get input from the user
    string cityName = "";
    float radius;
    while (cityName != "0")
    {
        std::cout << "Please enter selected city name (with line break after it):";
        std::getline(std::cin, cityName);
        auto it = myMap.find(cityName);
        if (it == myMap.end())
        {
            std::cout << "ERROR: “Alabaster AL” isn't found in the city list. Please try again.";
            continue;
        }
            std::cout << "Please enter the wanted radius :";
            std::cin >> radius;
            Location& city_location = it->second;
            float lat_loc= city_location._latitude;
            float long_loc = city_location._longitude;
            std::multimap<std::string, Location > matchingElements;
            // copy all the elements that are in the square with the wanted radius
            std::copy_if(myMap.begin(), myMap.end(), std::inserter(matchingElements, matchingElements.end()),
                 [long_loc,lat_loc, radius]
                 (const std::pair<const std::string, Location>& element)
                    {
                     return std::abs(element.second._latitude - lat_loc) <= radius 
                         && std::abs(element.second._longitude - long_loc) <= radius;
                 });
            std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):";
            int norm;
            std::cin >> norm;
            map<int, std::function <float (const Location&, const Location&)> > choose_norm;
            choose_norm[0] = L2;
            choose_norm[1] = Linf;
            choose_norm[2] = L1;
            std::multimap<std::string,Location > sortedMatches;
            std::copy_if(matchingElements.begin(), matchingElements.end(),
                std::inserter(sortedMatches, sortedMatches.end()),
                [&city_location, &radius, &norm, &choose_norm]
                (std::pair<const std::string, Location>& element) 
                {
                    return choose_norm[norm](city_location, element.second) < radius;
                });
        
             std::cout<< sortedMatches.size()<< " city/cities found in the given radius." << std::endl;
             int count = std::count_if(sortedMatches.begin(), sortedMatches.end()
                 ,[long_loc]
                    (const std::pair<std::string, Location>& element)
                    {
                     return (element.second._longitude - long_loc) > 0;
                     });
             std::cout<<count<<"cities are to the north of the selected city."<<std::endl;
             std::cout<<"city list:"<<std::endl;
             
            std::transform(matchingElements.begin(), matchingElements.end()
                    , std::ostream_iterator<std::string>(std::cout, "\n"),
                [](const std::pair<const std::string, Location>& element) {
                    return element.first;
                });
        
    }
        std::cout << "Bye";
    

	return 0;
}