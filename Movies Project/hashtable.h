#ifndef HashTable_H
#define HashTable_H

#define MAXTABLESIZE 10

#include <iostream>
#include <vector>
using namespace std;

#include "customer.h"

class HashTable {
public:
  // default constructor for hashtable
  HashTable();

  // destructor for hash table
  ~HashTable();

  // function to add customer into hash table
  bool insert(Customer *customer);

  // fuction that retrieves customer  with given id
  Customer *get(const int id);

  // function that returns size of hash
  int size() const;

  // function that removes customer with given id
  bool remove(const int id);

  // function that prints allcustomer
  void printAll();

  // fuction that gets data from hash annd stores it as vector
  vector<Customer *> getAll();

private:
  // node structure representinf a node in link list
  struct Node {
    // has 3 members: id, pointer to customer object and pointer to next node in
    // linked list
    int id;
    Customer *customer;
    Node *next;
    // constructor to initiliaze id, customer members with given value and sets
    // next to nullptr
    Node(int id, Customer *customer)
        : id(id), customer(customer), next(nullptr) {}
  };
  // customerTable is vector pointer to Node
  std::vector<Node *> customerTable;
  // this fuction used for generating hash value based on an id
  int hashFunction(int id);
};

#endif