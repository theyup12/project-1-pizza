#pragma once
#include <fstream>
#include <sstream>
#include <string>

using std::getline;
using std::ifstream;
using std::string;
using std::stringstream;

// location class
class Location {
public:
  string name, address, city, province;
  long int postalCode;
  int priceRangeMax, priceRangeMin;
  double latitude, longitude;
};
