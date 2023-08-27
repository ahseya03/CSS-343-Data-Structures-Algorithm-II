
#include "classic.h"
#include <sstream>
// default constructor
Classic::Classic() {
  stock = 0;
  directorName = "";
  title = "";
  actorAndRelease = "";
  releaseYear = 0;
  type = ' ';
  genre = ' ';
}
// parameterized  cnstructor that takes string argument called line
Classic::Classic(const string &line) {
  stringstream parser(line);
  // each extracted piece of data from line is distinct value
  // with help of stringstream we assign all distinct values to variable
  string part;

  getline(parser, part, ',');
  type = part[0];

  getline(parser, part, ',');
  stock = stoi(part);

  getline(parser, part, ',');
  directorName = part;

  getline(parser, part, ',');
  title = part;

  getline(parser, part);
  actorAndRelease = part;
}

// parameterized constructor
// setting all values
Classic::Classic(int stock, string name, string title, string actorAndRelease,
                 int release, char type, char genre) {

  this->stock = stock;
  this->directorName = name;
  this->title = title;
  this->actorAndRelease = actorAndRelease;
  this->releaseYear = release;
  this->type = type;
  this->genre = genre;
}

// destructor
Classic::~Classic() {}

// setter for actor and release info
void Classic::setActorAndRelease(string actorAndRelease) {
  actorAndRelease = actorAndRelease;
}

// getter for actor and release info
string Classic::getActorAndRelease() { return actorAndRelease; }

// returns true if movie actor And Release Year less than false otherwise
bool Classic::operator<(Classic &other) const {
  return actorAndRelease < other.getActorAndRelease();
}

// return true if movie actor And Release Year greater false otherwise
bool Classic::operator>(Classic &other) const {
  return actorAndRelease > other.getActorAndRelease();
}

// return true if the movie actor And Release Year are same, false otherwise

bool Classic::operator==(Classic &other) const {
  return actorAndRelease == other.getActorAndRelease();
}
// returns true if movie  actor And Release Year not equal false otherwise

bool Classic::operator!=(Classic &other) const {
  return actorAndRelease != other.getActorAndRelease();
}