#include "movie.h"

// constructor for movie class
Movie::Movie() {

  stock = 0;
  directorName = "";
  title = "";
  releaseYear = 0;
  type = ' ';
  genre = ' ';
  oldStock = 0;
}

// parameterized constructor for movie
Movie::Movie(int stock, string name, string title, int release, char type,
             char genre) {

  this->stock = stock;
  this->directorName = name;
  this->title = title;
  this->releaseYear = release;
  this->type = type;
  this->genre = genre;
  this->oldStock = stock;
  //
}
// destructor for movie class
Movie::~Movie() {

  // For testing destructor
}
void Movie::borrowMovie() {
  if (stock > 0) {
    stock--;
  } else {
    cout << "out of stock" << endl;
  }
}
// function to get all number of movies in the store set
int Movie::getNumberOfMovies() const { return stock; }

// function to set number of movies in store
void Movie::setNumberOfMovies(int stock) { this->stock = stock; }

// returns char  getter function for getting type of movie in store set

char Movie::getType() const { return type; }

// function to set type of movie
void Movie::setType(char t) { type = t; }

// function to get genre of movie
char Movie::getGenre() const { return genre; }

// function to set genre of movie
void Movie::setGenre(char g) { genre = g; }

// getter function to get director first name
string Movie::getDirectorName() const { return directorName; }

/// setter function to set director first name
void Movie::setDirectorName(string firstName) { directorName = firstName; }

// getter function to  get title of movie
string Movie::getTitle() const { return title; }

// setter function to set title of movie
void Movie::setTitle(string title) { title = title; }

// getter function to get release year
int Movie::getReleaseYear() const { return releaseYear; }

// setter function to set release year
void Movie::setReleaseYear(int releaseYear) { releaseYear = releaseYear; }

// function to get Actor and release information
string Movie::getActorAndRelease() const { return actorAndRelease; }

// function to set Actor and release information
void Movie::setActorAndRelease(string actorAndReleaseYear) {
  actorAndRelease = actorAndReleaseYear;
}
// // returns true if movie actor And Release Year less than false otherwise

// bool Movie::operator<(const Movie &other) const { return false; }

// // return true if movie actor And Release Year greater false otherwise
// bool Movie::operator>(const Movie &other) const { return false; }

// // return true if the movie actor And Release Year are same, false otherwise

// bool Movie::operator==(const Movie &other) const { return false; }

// // returns true if movie  actor And Release Year not equal false otherwise
// bool Movie::operator!=(const Movie &other) const { return false; }

// ostream to help print movie title
ostream &operator<<(ostream &out, const Movie &movie) {
  out << movie.getTitle() << endl;
  return out;
}