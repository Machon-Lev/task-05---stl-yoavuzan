#include <iostream>
#include <map>
#include <string>
#include "Location.cpp"
#include <fstream>
using namespace std;
std::string PATH_TO_FILE = "C:\\Users\\becky\\Source\\Repos\\Task06_Yoav_Uzan\\Task06_Yoav_Uzan\\resources\\data.txt";

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

    inputFile.close();

    // get input from the user
    string cityName = "";
    float radius;
    while (cityName != "0")
    {
        cout << "Please enter selected city name (with line break after it):";
        cin >> cityName;
        auto it = myMap.find(cityName);
        if (it == myMap.end())
        {
            cout << "ERROR: “Alabaster AL” isn't found in the city list. Please try again.";
        }
        cout << "Please enter the wanted radius :";
        cin >> radius;
        cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):";
    
    }
    cout << "Bye";


	return 0;
}