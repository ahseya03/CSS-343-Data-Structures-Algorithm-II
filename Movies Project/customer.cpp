#include "customer.h"
#include <sstream>
// default constructor
Customer::Customer() {
  ID = 0;
  fName = "";
  lName = "";
  numberOfTransactions = 0;
}
// destructor
Customer::~Customer() {}
// parameterized constructor
Customer::Customer(int ID, string firstName, string lastName) {
  // checks for bad input
  if (ID != 0 && !firstName.empty() && !lastName.empty()) {
    this->ID = ID;
    this->fName = firstName;
    this->lName = lastName;
    numberOfTransactions = 0;
  }
}
// function that retuens id of customer
int Customer::getID() const { return ID; }
// getter function that returns string representation of first name
string Customer::getFirstName() const { return fName; }
// setter function that sets first name
void Customer::setFirstName(string firstname) { this->fName = firstname; }
// getter function that gets last name
string Customer::getLastName() const { return lName; }
// setter function that sets customer last name
void Customer::setLastName(string lastName) { this->lName = lastName; }
// function to log transaction takes in key title of movie and action 'B' or
// 'R'(BOrrowing or returning)

void Customer::logTransaction(string key, string action) {
  history[numberOfTransactions][0] = key;
  history[numberOfTransactions][1] = action;
  history[numberOfTransactions][2] = "";
  numberOfTransactions++;
  if (numberOfTransactions == 0) {
    cout << "    "
         << "No transaction history" << endl;
  }
}

// function to display transaction history of cystomer
void Customer::displayTransaction() {

  cout << "Transaction history log for " << getFirstName() << " "
       << getLastName() << endl;
  // intializing index as integer
  int index = 0;
  for (int i = 0; i < numberOfTransactions; i++) {
    // printing of index and all info stored inside array
    cout << ++index << ". " << history[i][2] << " " << history[i][0] << " "
         << history[i][1] << endl;
  }
}
// function that returns total number of transaction
int Customer::getNumberOfTransactions() { return numberOfTransactions; }

bool Customer::borrowedMovie(string cmd, string info) {
  if (numberOfTransactions == 0) {

    return false;
  }

  for (int i = numberOfTransactions - 1; i >= 0; i--) {
    if (history[i][1] == cmd && history[i][0] == info) {
      return true;
    }
  }
  return false;
}