// Ayesha Mahmood
// Rectangle Class
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Rectangle : public SVG {

public:
  // operator overload to write rectangle data
  ostream &write(ostream &out) const override;

  // operator overload to read rectangle data
  istream &read(istream &input) override;

private:
  // initializing corners and radius of rectangle
  int x{0}, y{0};

  int rx{0}, ry{0};

  // for length and width
  int width{0}, height{0};

  // for rotation
  int transform{0};

  // intializing with default color of rectangle
  string color{"red"};
};

#endif