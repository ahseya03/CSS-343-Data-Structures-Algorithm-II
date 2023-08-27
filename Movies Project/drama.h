
#pragma once
#include "movie.h"

// Drama class inherited from movie class
class Drama : public Movie {
  // public method
public:
  // default constructor
  Drama();

  // parameterized  constructor that takes string argument called line
  Drama(const string &line);

  // parameterized constructor
  Drama(int stock, string name, string title, int release, char type,
        char genre);

  // virtual destructor
  virtual ~Drama();

  // returns true if director name is less than false otherwise
  virtual bool operator<(const Movie &rhs) const;

  // return true if director names is greater than false otherwise
  virtual bool operator>(const Movie &rhs) const;

  // return true if director names are equal false otherwise
  virtual bool operator==(const Movie &rhs) const;

  // returns true if direction names are not equal
  virtual bool operator!=(const Movie &rhs) const;
};