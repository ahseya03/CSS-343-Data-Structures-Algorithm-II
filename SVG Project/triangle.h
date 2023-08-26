// Ayesha Mahmood
// Triangle Class
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Triangle : public SVG {

public:
  // opwrator overload to write object content
  ostream &write(ostream &out) const override;

  // operator overload to read object contents
  istream &read(istream &input) override;

private:
  // initializing all vertices of triangle
  int vertex1{0}, vertex2{0}, vertex3{0}, vertex4{0}, vertex5{0}, vertex6{0};

  // intializing color for triangle with default color
  string color{"blue"};
};

#endif