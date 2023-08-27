// Ayesha Mahmood
// Instructor: Professor Pisan
// June 1 , 2023

// including header file store.hg
#include "store.h"
#include <algorithm>
#include <iostream>
using namespace std;

// Default Constructor for Store
Store::Store() {}
// Destructor for Store Class
Store::~Store() {

  for (Movie *movie : moviesC) {
    delete movie;
  }

  for (Movie *movie : moviesD) {
    delete movie;
  }

  for (Movie *movie : moviesF) {
    delete movie;
  }
}

void Store::buildMovieList(ifstream &movies) {
  if (!movies.is_open()) {
    cout << "Error opening movie file" << endl;
    return;
  }

  string line;
  while (getline(movies, line)) {
    istringstream parser(line);
    string genre;
    if (getline(parser, genre, ',')) {
      if (genre == "F" || genre == "D") {
        string stock;
        string director;
        string title;
        string year;
        if (getline(parser, stock, ',') && getline(parser, director, ',') &&
            getline(parser, title, ',') && getline(parser, year, ',')) {

          // Check for invalid movie entries
          if (stock.empty() || director.empty() || title.empty() ||
              year.empty()) {
            cout << "Invalid movie entry: " << line << endl;
            continue;
          }

          if (genre == "F") {
            Movie *movieF =
                new Movie(stoi(stock), director, title, stoi(year), 'D', 'F');
            moviesF.push_back(movieF);
          } else if (genre == "D") {
            Movie *movieD =
                new Movie(stoi(stock), director, title, stoi(year), 'D', 'D');
            moviesD.push_back(movieD);
          }
        } else {
          cout << "Invalid movie entry: " << line << endl;
        }
      } else if (genre == "C") {
        string stock;
        string director;
        string title;
        string yearInfo;
        if (getline(parser, stock, ',') && getline(parser, director, ',') &&
            getline(parser, title, ',') && getline(parser, yearInfo)) {

          // Check for invalid movie entries
          if (stock.empty() || director.empty() || title.empty() ||
              yearInfo.empty()) {
            cout << "Invalid movie entry: " << line << endl;
            continue;
          }

          size_t spacePos = yearInfo.find_last_of(' ');
          string actorFullName = yearInfo.substr(0, spacePos);
          string yearStr = yearInfo.substr(spacePos + 1);
          int year = stoi(yearStr);

          Movie *movieC = new Classic(stoi(stock), director, title,
                                      actorFullName + " " + to_string(year),
                                      year, 'D', 'C');
          moviesC.push_back(movieC);
        } else {
          cout << "Invalid movie entry: " << line << endl;
        }
      } else {
        cout << "Invalid genre type: " << genre << endl;
      }
    }
  }

  movies.close();
}

// function that will create customer list, ifstream object takes refere
void Store::buildCustomerList(ifstream &customers) {
  if (!customers.is_open()) {
    cout << "Error opening customer file" << endl;
    return;
  }
  while (!customers.eof()) {

    // intializing data related to customer as strong
    string last;
    string first;
    int ID;
    // input stream extraction for ID last and first name
    customers >> ID >> last >> first;

    // checking for bad input if id not 0 or fullname is not present
    if (ID != 0 && !first.empty() && !last.empty()) {
      // if valid input adds customer to list
      Customer *customerInfo = new Customer(ID, last, first);
      customerList.insert(customerInfo);
    }
  }
  customers.close();
}
// returns int getter funcion to get number of Customer
int Store::getNumberOfCustomers() { return customerList.size(); }
// this function will help find customer by ID

string Store::findByID(int id) {
  // searcher pointer to Customer object to find id
  Customer *search = customerList.get(id);
  // as long as search pointer not null i.e customer with given name is found

  if (search != NULL) {
    string firstName = search->getFirstName();
    string lastName = search->getLastName();
    // return the full name of person with id
    return firstName + " " + lastName;
  }
  // else return not found message
  return "The person with given id not found: Invalid ID";
}
// Bool  function that take  id of customer to remove customer
bool Store::removeByID(int id) {
  // search pointer to Customer object to find id
  Customer *search = customerList.get(id);
  // as long as search pointer not null i.e customer with given name is found
  if (search != nullptr) {
    // remove id from list
    customerList.remove(id);
    // delete search pointer to avoid memory leaks
    delete search;
    // return true for successful deletion
    return true;
  }
  // return false if id not found
  return false;
}
// function to add customer with their info
bool Store::addCustomer(int id, string firstName, string lastName) {
  // search pointer to Customer object to find id
  Customer *search = customerList.get(id);
  // if search is null) i.e if no customer with same ID exists
  if (search == nullptr) {
    // create temporary pointer to Customer object to add  customer with given
    // information
    Customer *customerToAdd = new Customer(id, firstName, lastName);
    // add customer to list
    customerList.insert(customerToAdd);
    return true;
  }
  // unsuccessful i.e. customer with same ID exists
  return false;
}
// function to update customer's info
bool Store::updateInfo(int id, string firstName, string lastName) {
  Customer *customerToUpdate = customerList.get(id);
  // as long customerToUpdate pointer not null i.e customer with given name is
  // found
  if (customerToUpdate != nullptr) {
    // update customer first and last name
    customerToUpdate->setFirstName(firstName);
    customerToUpdate->setLastName(lastName);
  }
  return false;
}
// function to execute all command takes in the command line as parameter
bool Store::executeCommand(string command) {
  // if first index of command line if 'I'
  if (command[0] == 'I') {

    sort(moviesF.begin(), moviesF.end(), [](Movie *a, Movie *b) {
      if (a->getTitle() != b->getTitle()) {
        return a->getTitle() < b->getTitle();
      } else {
        return a->getReleaseYear() < b->getReleaseYear();
      }
    });

    // Sort the Drama movies by Director, then Title
    sort(moviesD.begin(), moviesD.end(), [](Movie *a, Movie *b) {
      if (a->getDirectorName() != b->getDirectorName()) {
        return a->getDirectorName() < b->getDirectorName();
      } else {
        return a->getTitle() < b->getTitle();
      }
    });

    // Sort the Classic movies by Release date, then Major actor
    sort(moviesC.begin(), moviesC.end(), [](Movie *a, Movie *b) {
      if (a->getReleaseYear() != b->getReleaseYear()) {
        return a->getReleaseYear() < b->getReleaseYear();
      } else {
        return a->getActorAndRelease() < b->getActorAndRelease();
      }
    });

    cout << "================= Inventory List of all Items in Store "
            "================="
         << endl;

    cout << "Genre : Comedy" << endl;
    for (Movie *movieF : moviesF) {
      cout << "\t" << movieF->getGenre() << " " << movieF->getType() << " "
           << movieF->getNumberOfMovies() << " " << movieF->getDirectorName()
           << " " << movieF->getTitle() << " " << movieF->getReleaseYear()
           << endl;
    }
    cout << "\n================= Summary of Total Borrowed And "
            "Remaining(Comedy Movie) "
            "================="
         << endl;
    for (Movie *movieF : moviesF) {
      std::ifstream inputFile("data4movies.txt");
      if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
      }

      std::string line;
      std::getline(inputFile, line);

      std::istringstream iss(line);
      char ch;
      int num;

      std::string charString;
      std::getline(iss, charString, ',');
      std::istringstream(charString) >> ch;

      std::string numString;
      std::getline(iss, numString);
      std::istringstream(numString) >> num;

      inputFile.close();

      cout << movieF->getTitle() << "(" << movieF->getDirectorName() << ", "
           << movieF->getReleaseYear() << ") "
           << "\n\t Borrowed count: " << num - movieF->getNumberOfMovies()
           << "\n"
           << "\t Movies remaining: " << movieF->getNumberOfMovies() << "\n"
           << endl;
    }
    cout << "=================================================================="
            "======================"
         << endl;

    cout << "Genre : Drama" << endl;
    for (Movie *movieD : moviesD) {

      cout << "\t" << movieD->getGenre() << " " << movieD->getType() << " "
           << movieD->getNumberOfMovies() << " " << movieD->getDirectorName()
           << " " << movieD->getTitle() << " " << movieD->getReleaseYear()
           << endl;
    }
    cout << "\n================= Summary of Total Borrowed And Remaining(Drama "
            "Movie) "
            "================="
         << endl;
    for (Movie *movieD : moviesD) {
      std::ifstream inputFile("data4movies.txt");
      if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
      }

      std::string line;
      std::getline(inputFile, line);

      std::istringstream iss(line);
      char ch;
      int num;

      std::string charString;
      std::getline(iss, charString, ',');
      std::istringstream(charString) >> ch;
      std::string numString;
      std::getline(iss, numString);
      std::istringstream(numString) >> num;

      inputFile.close(); // Close the input file
      cout << movieD->getTitle()
           << "\n\t Borrowed count: " << num - movieD->getNumberOfMovies()
           << "\n"
           << "\t Movies remaining: " << movieD->getNumberOfMovies() << "\n"
           << endl;
    }
    cout << "=================================================================="
            "======================"
         << endl;

    cout << "Genre : Classic" << endl;
    for (Movie *movieC : moviesC) {
      cout << "\t" << movieC->getGenre() << " " << movieC->getType() << " "
           << movieC->getNumberOfMovies() << " " << movieC->getDirectorName()
           << " " << movieC->getTitle() << " " << movieC->getActorAndRelease()
           << endl;
    }
    cout << "\n================= Summary of Total Borrowed And "
            "Remaining(Classic Movie) "
            "================="
         << endl;
    for (Movie *movieC : moviesC) {
      std::ifstream inputFile("data4movies.txt");
      if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
      }

      std::string line;
      std::getline(inputFile, line);

      std::istringstream iss(line);
      char ch;
      int num;

      std::string charString;
      std::getline(iss, charString, ',');
      std::istringstream(charString) >> ch;

      std::string numString;
      std::getline(iss, numString);
      std::istringstream(numString) >> num;

      inputFile.close(); // Close the input file
      cout << movieC->getTitle() << "(" << movieC->getActorAndRelease() << ")"
           << "\n\t Borrowed count: " << num - movieC->getNumberOfMovies()
           << "\n"
           << "\t Movies remaining: " << movieC->getNumberOfMovies() << "\n"
           << endl;
    }
    cout << "=================================================================="
            "======================"
         << endl;

  } else if (command[0] == 'H') {

    string type;
    string ID;
    stringstream s;
    s << command;
    s >> type;
    s >> ID;

    int id = atoi(ID.c_str());
    showHistory(id);

  }

  else if (command[0] == 'B' || command[0] == 'R') {

    string act;
    int ID;
    string type;
    char genre;
    stringstream s;
    s << command;
    s >> act;
    s >> ID;
    s >> type;
    s >> genre;

    Customer *cus = customerList.get(ID);
    if (cus == nullptr) {
      cout << "There is no customer: " << ID << endl;
      return false;
    }

    if (genre == 'F') {

      int pos1 = subStrAt(command, 3, ' ');
      int pos2 = subStrAt(command, 0, ',');

      string title = command.substr(pos1, (pos2 - pos1));
      string info = command.substr(0);

      for (int i = 0; i < moviesF.size(); i++) {
        if (moviesF[i]->getTitle() == title) {

          if (command[0] == 'B') {

            cus->logTransaction(command, "(Borrowed)");

            updateStock(-1, moviesF[i]);

            return true;
          }

          if (command[0] == 'R') {
            // if(!cus->borrowedMovie("(Borrowed)",command)){
            //   cout<<"can''t return movie borrowed"<<command
            //   <<endl;
            // }
            if (cus != nullptr) {

              cus->logTransaction(command, "(Returned)");
              updateStock(1, moviesF[i]);

              return true;
            } else {
              cout << "Customer not found" << endl;
            }
          }
        }
      }
      cout << "Movie:" << title
           << "(Not found), therefore your transaction: " << command
           << "(Failed)" << endl;
    }
    if (genre == 'D') {

      int pos1 = subStrAt(command, 3, ' ');
      int pos2 = subStrAt(command, 0, ',');
      string dir = command.substr(pos1, (pos2 - pos1));

      pos1 = subStrAt(command, 0, ',');
      pos2 = subStrAt(command, 1, ',');
      string title = command.substr(pos1 + 1, (pos2 - pos1) - 1);
      // check every movies
      for (int i = 0; i < moviesD.size(); i++) {
        if (moviesD[i]->getTitle() == title) {
          if (command[0] == 'B') {
            cus->logTransaction(command, "(Borrowed)");

            updateStock(-1, moviesD[i]);

            return true;
          }
          if (command[0] == 'R') {
            // if(!cus->borrowedMovie("(Borrowed)",command)){
            //   cout<<"can''t return movie borrowed"<<command
            //   <<endl;
            // }

            if (cus != nullptr) {

              cus->logTransaction(command, "(Returned)");
              updateStock(1, moviesD[i]);

              return true;
            } else {
              cout << "Customer not found" << endl;
            }
          }
        }
      }
      cout << "Movie:" << title
           << "(Not found), therefore your transaction: " << command
           << "(Failed)" << endl;
    }

    if (genre == 'C') {

      int pos1 = subStrAt(command, 3, ' ');
      int pos2 = subStrAt(command, 5, ' ');
      string myear = command.substr(pos1, (pos2 - pos1));

      pos1 = subStrAt(command, 5, ' ');
      pos2 = command.length();
      string act = command.substr(pos1 + 1, (pos2 - pos1) - 1);
      for (int i = 0; i < moviesC.size(); i++) {
        if (moviesC[i]->getActorAndRelease() == (" " + act + myear)) {
          if (command[0] == 'B') {
            if (cus != nullptr) {
              cus->logTransaction(command, "(Borrowed)");

              updateStock(-1, moviesC[i]);

              return true;
            } else {
              cout << "Customer not found" << endl;
            }
          }

          if (command[0] == 'R') {
            // if(!cus->borrowedMovie("(Borrowed)",command)){
            //   cout<<"can''t return movie borrowed"<<command
            //   <<endl;
            // }
            if (cus != nullptr) {

              cus->logTransaction(command, "(Returned)");
              updateStock(1, moviesC[i]);

              return true;
            } else {
              cout << "Movie:" << act
                   << "(Not found), therefore your transaction: " << command
                   << "(Failed)" << endl;
            }
          }
        }
      }
      cout << command << "not found" << endl;
    }

  }
  // check for bad input
  else {
    cout << "Invalid command type! " << command[0] << endl;
    return false;
  }
  return true;
}

bool Store::executeCommandFile(ifstream &commands) {
  string line;
  // loop continues as long as there are lines in file it gets the line
  while (getline(commands, line)) {
    // calls excute command on line which execute command according to command
    // input in the line
    executeCommand(line);
  }
  // return false if no lines
  return false;
}
// this function displays history of all transaction of customer
bool Store::showHistory(int id) {
  // pointer to customer object called customer
  Customer *customer;
  // retrieves customer object from customer list based on id given and stores
  // it into temporary customer pointer

  customer = customerList.get(id);
  if (!customer) {

    delete customer;
  }
  // edge case: if customer's number of transaction are 0
  if (customer->getNumberOfTransactions() == 0) {
    // prints error
    cout << "=======================================================" << endl;
    cout << "There is no history for  " << customer->getFirstName() << " "
         << customer->getLastName() << endl;
    cout << "=======================================================" << endl;
    return false;
  } else
    // else returns summary of all transactions of customer
    cout << "=======================================================" << endl;
  cout << "History Summary of all transactions of the customer" << endl;

  customer->displayTransaction();
  return true;
}
// function to print all customers
void Store::printAllCustomer() {

  for (const auto &customer : customerList.getAll()) {
    cout << "\t"
         << "Customer ID: " << customer->getID() << " Full Name: "
         << " " << customer->getFirstName() << " " << customer->getLastName()
         << endl;
  }
}

bool Store::updateStock(
    int stockChange, Movie *movie) { // getting current number in stock of movie
  int currentStock = movie->getNumberOfMovies();

  // intializing newValue which representated calculated value of new stock
  // quantity after applying stock change(if plus indicating increase in stock)
  // and if minus(indicates decrease in stock)
  int newValue = currentStock + stockChange;

  // if calculated stock value is less than 0 indicates that the stock would be
  // negative as not enough available

  if (newValue < 0) {
    cout << movie->getTitle() << " not available in stock" << endl;
    return false;
  }

  // else updates the stock value
  movie->setNumberOfMovies(newValue);

  return true;
}
int Store::subStrAt(string str, int index, char sign) {
  int count = 0;
  int pos = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == sign) {
      count++;
    }
    if (count == index) {
      pos = i;
    }
  }

  return (pos + 1);
}
