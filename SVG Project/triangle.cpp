#include "triangle.h"
#include <fstream>
#include <iostream>

using namespace std;

// overload ostream to write out color and vertex
ostream &Triangle::write(ostream &out) const {
  out << "      <polygon ";
  out << "points=\"" << vertex1 << "," << vertex2 << " " << vertex3 << ","
      << vertex4 << " " << vertex5 << "," << vertex6 << "\" ";
  out << "style=\"fill:" << color << "\" ";
  out << " />" << endl;
  return out;
}
// istream to read in scale for vertex and color
istream &Triangle::read(istream &input) {
  input >> vertex1 >> vertex2 >> vertex3 >> vertex4 >> vertex5 >> vertex6 >>
      color;
  return input;
}