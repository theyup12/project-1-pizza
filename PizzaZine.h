#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "Location.h"

using std::getline;
using std::ifstream;
using std::string;
using std::stringstream;

class PizzaZine {
private:
  Location *pizzaLocations;
  size_t size;

public:
  PizzaZine(const size_t & = 50);
  ~PizzaZine();
  Location &operator[](size_t);

  // This function is implemented for you
  void readInFile(const string &);
};
// constructor
PizzaZine::PizzaZine(const size_t &size_) {
  size = size_;
  pizzaLocations = new Location[size_];
}
// use to return the location in the list
Location &PizzaZine::operator[](size_t index) {
  return pizzaLocations[index];
}
// destructors
PizzaZine::~PizzaZine() { delete[] pizzaLocations; }

void PizzaZine::readInFile(const string &filename) {
  ifstream inFile(filename);
  Location newLoc;

  string line;
  string cell;

  // Read each line
  for (int i = 0; i < size; ++i) {
    // Break each line up into 'cells'
    getline(inFile, line);
    stringstream lineStream(line);
    while (getline(lineStream, newLoc.name, ',')) {
      getline(lineStream, newLoc.address, ',');
      getline(lineStream, newLoc.city, ',');
      getline(lineStream, cell, ',');
      if (!cell.empty()) {
        newLoc.postalCode = stoul(cell);
      }

      getline(lineStream, newLoc.province, ',');
      getline(lineStream, cell, ',');
      newLoc.latitude = stod(cell);
      getline(lineStream, cell, ',');
      newLoc.longitude = stod(cell);

      newLoc.priceRangeMin = -1;
      getline(lineStream, cell, ',');
      if (!cell.empty()) {
        newLoc.priceRangeMin = stoul(cell);
      }

      newLoc.priceRangeMax = -1;
      getline(lineStream, cell, ',');
      if (!cell.empty() && cell != "\r") {
        newLoc.priceRangeMax = stoul(cell);
      }
      pizzaLocations[i] = newLoc;
    }
  }
}
