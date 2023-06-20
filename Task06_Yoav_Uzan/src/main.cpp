#include <functional>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include "Location.cpp"
#include <fstream>
#include <filesystem>

float L2( const Location& loc1, const Location& loc2)
{
    // dis= sqrt((x1-x2)^2+(y1-y2)^2)
	return std::sqrt(std::pow(loc1._latitude - loc2._latitude, 2) + std::pow(loc1._longitude - loc2._longitude, 2));
}

float L1(const Location& loc1, const Location& loc2)
{
    // dis= |x1-x2|+|y1-y2|
	return std::abs(loc1._latitude - loc2._latitude) + std::abs(loc1._longitude - loc2._longitude);
}

float Linf(const Location& loc1, const Location& loc2)
{
    // dis= max(|x1-x2|,|y1-y2|)
	return std::max(std::abs(loc1._latitude - loc2._latitude), std::abs(loc1._longitude - loc2._longitude));
}

struct SortByMap {
    std::function<float(const Location&, const Location&)> calcDistance;
    Location centeralCityLocation;

    SortByMap(std::function<float(const Location&, const Location&)> func, const Location& param)
        : calcDistance(std::move(func)), centeralCityLocation(param) {}

    bool operator()(const std::pair<const std::string, Location>& a, const std::pair<const std::string, Location>& b) const {
        return calcDistance(a.second, centeralCityLocation) < calcDistance(b.second, centeralCityLocation);
    }
};


int main() {
	
  try
  {
      std::multimap<std::string, Location > myMap;
     //read in the data from the file data.txt and store it in the map
     std::ifstream inputFile("data.txt");
        if (!inputFile.is_open()) 
            throw std::runtime_error("Failed to open file: data.txt");
        
        std::string line1, line2;
        while (std::getline(inputFile, line1)) {
            std::getline(inputFile, line2);

            myMap.insert({ line1, {Location(line2)} });
        }
        inputFile.close();
    // get input from the user
    std::cout << "Please enter selected city name (with line break after it):";
    std::string cityName = "";
    std::getline(std::cin, cityName);
    float radius;

    //responsible for choosing the wanted norm L2, L1 or Linf {0:L2,1:Linf,2:L1}
    std::map<int, std::function <float(const Location&, const Location&)> > choose_norm;
    choose_norm[0] = L2;
    choose_norm[1] = Linf;
    choose_norm[2] = L1;
    
    while (cityName != "0")
    {    
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
             [&long_loc,&lat_loc, &radius]
             (const std::pair<const std::string, Location>& element)
             {
              return std::abs(element.second._latitude - lat_loc) <= radius 
                     && std::abs(element.second._longitude - long_loc) <= radius;
             });
        //remove the selected city from the list
        matchingElements.erase(cityName);

        std::cout << "Please enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):";
        int norm;
        std::cin >> norm;
        std::multimap<std::string,Location> sortedMatches;
        
        // copy all the elements that are in the circle with the wanted radius
        std::copy_if(matchingElements.begin(), matchingElements.end(),
             std::inserter(sortedMatches, sortedMatches.end()),
                  [&city_location, &radius, &norm, &choose_norm]
                  (std::pair<const std::string, Location>& element) 
                  {
                    return choose_norm[norm](city_location, element.second) < radius;
                  });
      
        std::vector<std::pair< std::string,  Location>> sortedByNorn(sortedMatches.begin(), sortedMatches.end());
        std::sort(sortedByNorn.begin(), sortedByNorn.end(), SortByMap(choose_norm[norm], city_location));


      /*  matchingElements.sort([](const std::pair<std::string, Location>& element1, const std::pair<std::string, Location>& element2)
            {
				return choose_norm[norm](city_location, element1.second) < choose_norm[norm](city_location, element2.second);
			});*/
        
        std::cout<<"Search result:"<<std::endl;
        std::cout<< (sortedByNorn.size()+1)<< " city/cities found in the given radius." << std::endl;
        
        // count the number of cities that are to the north of the selected city
        int count = std::count_if(sortedMatches.begin(), sortedMatches.end()
                    ,[&lat_loc]
                    (const std::pair<std::string, Location>& element)
                    {
                     return (element.second._latitude - lat_loc) < 0;
                     });
        std::cout<<count<<" cities are to the north of the selected city."<<std::endl;
        std::cout<<"city list:"<<std::endl;
        std::transform(sortedByNorn.begin(), sortedByNorn.end()
                    , std::ostream_iterator<std::string>(std::cout, "\n"),
                    [](const std::pair<const std::string, Location>& element)
                    {
                    return element.first;
                    });
        
        // get input from the user
        std::cout << "Please enter selected city name (with line break after it):";
        cityName = "";
        std::cin.ignore();
        std::getline(std::cin, cityName);
    }
    std::cout << "Bye";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
	return 0;
}