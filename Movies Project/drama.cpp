// including header file
#include "drama.h"
#include <sstream>

// default constructor
Drama::Drama() {

  stock = 0;
  directorName = "";
  title = "";
  releaseYear = 0;
  type = ' ';
  genre = ' ';
}

// parameterized  constructor that takes string argument called line
Drama::Drama(const string &line) {

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

// parameterized constructor
// setting all values
Drama::Drama(int stock, string name, string title, int release, char type,
             char genre) {

  stock = stock;
  directorName = name;
  title = title;
  releaseYear = release;
  type = type;
  genre = genre;
}

// destructor
Drama::~Drama() {}

// returns true if director name is less than false otherwise
bool Drama::operator<(const Movie &other) const {
  return directorName < other.getDirectorName();
}

// return true if director names is greater than false otherwise
bool Drama::operator>(const Movie &other) const {
  return directorName > other.getDirectorName();
}

// return true if director names are equal false otherwise
bool Drama::operator==(const Movie &other) const {
  return directorName == other.getDirectorName();
}
// returns true if director names are not equal
bool Drama::operator!=(const Movie &other) const {
  return directorName != other.getDirectorName();
}