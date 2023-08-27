
#pragma once
#include "movie.h"
// classic inherited from movie class
class Classic : public Movie {

public:
  // default constructor
  Classic();

  // parameterized constructing taking in line argument
  Classic(const string &line);

  // parameterized constructor having all info related to classic movie
  Classic(int stock, string name, string title, string actorAndRelease,
          int release, char type, char genre);

  // virtual destructor
  virtual ~Classic();

  // setter for actor and release info
  void setActorAndRelease(string setActorAndRelease);
  // getter for actor and release info
  string getActorAndRelease();

  // returns true if movie less than false otherwise
  bool operator<(Classic &other) const;
  // return true if movie greater false otherwise

  bool operator>(Classic &other) const;
  // return true if the movies are same, false otherwise

  bool operator==(Classic &other) const;

  // returns true if movie not equal false otherwise

  bool operator!=(Classic &other) const;

private:
};