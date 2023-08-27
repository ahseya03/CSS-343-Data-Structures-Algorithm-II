#include "comedy.h"
#include <sstream>
// default constructor
Comedy::Comedy() {

  stock = 0;
  directorName = "";
  title = "";
  releaseYear = 0;
  type = ' ';
  genre = ' ';
}

// parameterized  constructor that takes string argument called line
Comedy::Comedy(const string &line) {
  stringstream parser(line);
  string part;
  // each extracted piece of data from line is distinct value
  // with help of stringstream we assign all distinct values to variable

  getline(parser, part, ',');
  type = part[0];

  getline(parser, part, ',');
  stock = atoi(part.c_str());

  getline(parser, part, ',');
  directorName = part;

  getline(parser, part, ',');
  title = part;

  getline(parser, part, ',');
  releaseYear = atoi(part.c_str());
}
// parametrized constructor
Comedy::Comedy(int stock, string name, string title, int release, char type,
               char genre) {

  this->stock = stock;
  this->directorName = name;
  this->title = title;
  this->releaseYear = release;
  this->type = type;
  this->genre = genre;
}

// destructor
Comedy::~Comedy() {}

// returns true if title name is less than false otherwise
bool Comedy::operator<(const Movie &other) const {
  return title < other.getTitle();
}

// return true if title names is greater than false otherwise
bool Comedy::operator>(const Movie &other) const {
  return title > other.getTitle();
}

// return true if title names are equal false otherwise
bool Comedy::operator==(const Movie &other) const {
  return title == other.getTitle();
}

// returns true if title names are not equal
bool Comedy::operator!=(const Movie &other) const {
  return title != other.getTitle();
}