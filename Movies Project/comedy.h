
#pragma once
#include "movie.h"

// comedy inherited from movie class
class Comedy : public Movie {

public:
  // default constructor
  Comedy();

  // parameterized  constructor that takes string argument called line
  Comedy(const string &line);

  // parameterized constructor
  Comedy(int stock, string name, string title, int release, char type,
         char genre);

  // virtual destructor
  virtual ~Comedy();
  //
  //   void borrowMovie();

  // returns true if title name is less than false otherwise
  virtual bool operator<(const Movie &other) const;

  // return true if title names is greater than false otherwise
  virtual bool operator>(const Movie &other) const;

  // return true if title names are equal false otherwise
  virtual bool operator==(const Movie &other) const;

  // returns true if title names are not equal
  virtual bool operator!=(const Movie &other) const;
};