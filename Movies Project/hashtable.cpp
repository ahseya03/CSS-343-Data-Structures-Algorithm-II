#include "hashtable.h"
// constructor that initializes customerTable  as a Vector of pointers to Node
// object
//  each elem is intialized to null ptr
HashTable::HashTable() { customerTable.resize(MAXTABLESIZE, nullptr); }
// hash function so we don't go over size
int HashTable::hashFunction(int id) { return (id % MAXTABLESIZE); }
// destructor dynamically allocates nodes in customerTable vector , it iterates
// through each element of the vector and delete node in linked list
HashTable::~HashTable() {
  for (int i = 0; i < customerTable.size(); i++) {
    // current pointer to node object refrencing the vector index
    Node *current = customerTable[i];
    // as long as not null ptr continue
    while (current != nullptr) {
      // assign tmp ptr of node object  to current
      Node *next = current->next;
      delete current->customer;
      delete current;
      current = next;

      // // keep advancing current till end of loop
      // current = current->next;
      // // deallocate  node
      // delete tmp;
    }
  }
}
// bool function to add to hashtable takes pointer to customer object as
// reference
bool HashTable::insert(Customer *customer) {
  // get customer id and assigning to id integer
  int id = customer->getID();
  // index set to hash function of the id
  int index = hashFunction(id);
  // intialize nodeToAdd as pointer to Node object
  Node *nodeToAdd = new Node(id, customer);
  // if the index empty we simply add to desired index after doing the formula
  // for hash by calling hash function on id
  if (customerTable[index] == nullptr) {
    customerTable[index] = nodeToAdd;
  } else {
    // else if not empty intialize current  pointer to node object that stores
    // current index
    Node *current = customerTable[index];
    // as long as what is afte not empty executes
    while (current->next != nullptr) {
      // base case if current id = the id we are tring to add return false since
      // duplicates not allowed
      if (current->id == id) {
        delete nodeToAdd;
        return false; //
      }
      current = current->next;
    } // important to check again in case last node in linked list has same id
    if (current->id == id) {
      delete nodeToAdd;
      return false; //
    }
    current->next = nodeToAdd;
  }
  return true;
}
// function to retrieve id
Customer *HashTable::get(const int id) {
  int index = hashFunction(id);
  // set current as pointer to node object  storing index of the table
  Node *current = customerTable[index];
  // as long as current is not nullptr
  while (current != nullptr) {
    // if current id = id trying to retrieve
    if (current->id == id) {
      // return
      return current->customer;
    } // else keep advancing
    current = current->next;
  }
  // if not found return nullptr
  return nullptr;
}
// function to get size  of hashtable
int HashTable::size() const {
  // initializing size to 0
  int size = 0;
  // for loop that runs to the size of customer table
  for (int i = 0; i < customerTable.size(); i++) {
    // current pointer to noject object keeps track of index we are at
    Node *current = customerTable[i];
    // as long as current doesnt reach null ptr
    while (current != nullptr) {
      // the size count increases
      size++;
      // the current index advances to next
      current = current->next;
    }
  }
  // at the end of loop total size returned
  return size;
}
// this function helps to remove id from hashtable , take in id as parameter
bool HashTable::remove(const int id) {
  // index set to hash of the id
  int index = hashFunction(id);
  // initialize current as ponter to node object storring the  hash index of
  // table
  Node *current = customerTable[index];
  // set previous as pointer to node and set to null
  Node *prev = nullptr;
  // as long as current not nullptr
  while (current != nullptr) {
    // if current id is equal to id
    if (current->id == id) {
      // if prev is null that means current node is first node in linked list
      if (prev == nullptr) {
        // therefore index updated to next ine  to effectively remove first
        customerTable[index] = current->next;
      } else {
        // else the case if there is a previous node in linked list, previous
        // next is updated to current one's next to to effectively remove
        prev->next = current->next;
      }
      // delele current
      // return tru to denote succesful deletion
      delete current;
      return true;
    }
    // set prev to current and current to currents next
    // keep advancing till matching id found
    prev = current;
    current = current->next;
  }
  // not found id
  return false;
}
// this function used to print id and full name of each customer
void HashTable::printAll() {
  for (int i = 0; i < MAXTABLESIZE; i++) {
    Node *current = customerTable[i];
    if (current != nullptr) {
      cout << "[";
      // adds leading 0 if index is less than 10 (FOR BETTER FORMATTING)

      if (i < 10) {
        cout << "0";
      }
      // prints out index of hash entry

      cout << i << "] => ";

      while (current != nullptr) {
        // as long as not null print out all customer information
        string fullName = current->customer->getFirstName() + " " +
                          current->customer->getLastName();
        cout << "[" << current->id << " " << fullName << "] ";
        current = current->next;
      }
      // prints new line

      cout << "\n";
    }
  }
}
// get all function
std::vector<Customer *> HashTable::getAll() {
  std::vector<Customer *> tmp;
  for (int i = 0; i < customerTable.size(); i++) {
    Node *current = customerTable[i];
    while (current != nullptr) {
      tmp.push_back(current->customer);
      current = current->next;
    }
  }
  return tmp;
}
