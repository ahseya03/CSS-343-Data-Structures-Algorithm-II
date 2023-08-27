// Ayesha Mahmood
// Instructor: Professor Pisan
// June 1 , 2023
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "hashtable.h"
#include "movie.h"

using namespace std;
class Store {

public:
  // default constructor
  Store();

  // destructor
  ~Store();

  // function to create movie list
  void buildMovieList(ifstream &movies);

  // function to build customer list
  void buildCustomerList(ifstream &customers);

  // function get number of customers
  int getNumberOfCustomers();

  // function to find customer id returns string representation of full name
  string findByID(int id);

  // bool function to remove customer by ID
  bool removeByID(int id);

  // addCustomer function to add customer  information
  bool addCustomer(int id, string firstName, string lastName);

  // function to update customer information
  bool updateInfo(int id, string firstName, string lastName);

  // function to print all customer
  // void printAllCustomer();
  void printAllCustomer();

  // function to execute commands
  bool executeCommand(string command);

  bool executeCommandFile(ifstream &commands);

  /// this function displays history of all transaction of customer
  bool showHistory(int id);

  int subStrAt(string str, int index, char sign);

private:
  // storing customerList in hashtable

  HashTable customerList;

  // vectors to store different types of Movies based on genre C, D , F
  vector<Movie *> moviesC;
  vector<Movie *> moviesD;
  vector<Movie *> moviesF;

  // bool function to update stock inventory of movie

  bool updateStock(int stockChange, Movie *movie);
};