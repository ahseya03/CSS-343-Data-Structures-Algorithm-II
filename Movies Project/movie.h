#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

class Movie {
  // overload ostream operator for movie class
  friend ostream &operator<<(ostream &out, const Movie &);
  // public methods
public:
  // default movie constructor
  Movie();

  // parameterized function for movie class holding movie information
  Movie(int stock, string name, string title, int release, char type,
        char genre);

  // destructor for movie class
  virtual ~Movie();

  // function that returns count of the number of movies in the store
  int getNumberOfMovies() const;

  // function to set number of movies in store
  void setNumberOfMovies(int stock);

  int getNumberBowrrowed() const;
  /// function to set number of movies in store
  void setNumberBorrowed(int stock);

  // returns char  getter function for getting type of movie in store set
  char getType() const;

  // function to set type of movie
  void setType(char type);

  // function to get genre of movie
  char getGenre() const;

  // function to set genre of movie
  void setGenre(char genre);

  // getter fuunction to get director first name
  string getDirectorName() const;

  // setter function to set director first name
  void setDirectorName(string firstName);

  // getter function to  get title of movie
  string getTitle() const;

  // setter function to set title of movie
  static void setTitle(string title);

  // getter function to get release year
  int getReleaseYear() const;

  // setter function to set release year
  static void setReleaseYear(int releaseYear);

  // function to get Actor and release information
  virtual string getActorAndRelease() const;

  // function to set Actor and release information
  virtual void setActorAndRelease(string actorAndReleaseYear);
  //borrow movie function
  void borrowMovie();
 
 

  //   // operator overload for > , <, ,==, != for comparing the movies
  //   virtual bool operator<(const Movie &other) const;

  //   virtual bool operator>(const Movie &other) const;

  //   virtual bool operator==(const Movie &other) const;

  //   virtual bool operator!=(const Movie &other) const;

protected:
  int moviesBorrowed;
  int moviesRemaining;
  int numberBorrowed;
  // intiliazing type of media
  char type;
  // intiliazing movie genre as char type
  char genre;
  // initializing stock as int type
  int stock;
  int oldStock;
  // intiliazing director name as string type
  string directorName;
  // initializing movie title as string time
  string title;
  // initializing release year as int type
  int releaseYear;
  // initializing actorAndRelease year as string type
  string actorAndRelease;
};