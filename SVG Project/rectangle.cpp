#include "rectangle.h"
#include <fstream>
#include <iostream>

using namespace std;

// operator overload for writing out object content , x is position of rectangle
// y being the width , both being on left side, and rx and ry refer to radius of
// the left side
// also writing the color , angle we should rotate
ostream &Rectangle::write(ostream &out) const {
  out << "      <rect ";
  out << "x=\"" << x << "\" ";
  out << "y=\"" << y << "\" ";
  out << "rx=\"" << rx << "\" ";
  out << "ry=\"" << ry << "\" ";
  out << "width=\"" << width << "\" ";
  out << "height=\"" << height << "\" ";
  out << "style=\"fill:" << color << "\" ";
  out << "transform=\"rotate()" << transform << "\" ";
  out << "stroke=\"" << color << "\" ";
  out << " />" << endl;

  return out;
}

// operator overload to read in rectangle data
istream &Rectangle::read(istream &input) {
  input >> x >> y >> rx >> ry >> width >> height >> color >> transform >> color;
  return input;
}