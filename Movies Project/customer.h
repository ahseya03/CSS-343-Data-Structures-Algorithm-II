#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAXLOG 1000

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Customer {
public:
  // default constructor for customer class
  Customer();

  // destructor
  ~Customer();

  // parameterized constructor
  Customer(int ID, string firstName, string lastName);

  // function that returns id
  int getID() const;

  // getter function that returns string representation of first name
  string getFirstName() const;

  // setter function that sets first name
  void setFirstName(string firstname);

  // getter function that gets last name
  string getLastName() const;

  // setter function that sets customer last name
  void setLastName(string lastName);

  // function to log transaction
  void logTransaction(string key, string action);

  // function that displays all transaction that occured
  void displayTransaction();

  // function that gets total number of transaction
  int getNumberOfTransactions();

  bool borrowedMovie(string cmd, string info);

private:
  // initializing ID as int
  int ID;
  // intialiing first name and last name as string
  string fName;
  string lName;
  // initializing numberOfTransACTION AS INT
  int numberOfTransactions;
  // 2 dimensional array that will store ltransaction history
  string history[MAXLOG][3];
  // maps that keeps tracks of available movies
  map<int, string> available;
};
#endif