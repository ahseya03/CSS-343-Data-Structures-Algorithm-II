
#include "autocomplete.h"
#include "bstmap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void testBSTAll();

void Autocomplete::readFile(const string &fileName) {
  // declaration defining input file stream called "if"and passing file name to
  // open
  ifstream ifs(fileName);
  // TODO(student)
  // edge case if file does not exist
  if (!ifs) {
    cerr << "file does not exist" << endl;
  }
  // declaration of string line and int number
  string line;
  int numberOfEntries;
  // reading line which is string and storing them into line
  getline(ifs, line);
  istringstream parser(line);
  // line parser for reading number (i.e for how many entries in file)
  parser >> numberOfEntries;
  // iterate through the number of entries in files
  for (int i = 0; i < numberOfEntries; i++) {
    // storing it into line string
    getline(ifs, line, '\t');
    // creating a stringstream object and then use the line input to parse it.
    istringstream parser(line);
    // initializing int variable to hold weight of keys
    int weight;
    // line parser for reading weight of keys
    parser >> weight;
    // declaration of string for key
    string key;
    // getline for reading key from input file
    getline(ifs, key, '\n');
    // assigning phrase key to its weight
    phrases[key] = weight;
  }
  // closing file
  ifs.close();
  // rebalancing phrase
  phrases.rebalance();
  // cout << phrases << endl;
}

// sort function
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// given a prefix gets all phrase that start with it, uses  sorts function to
// sort
// phrases by weight and prints them out
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);

  return v;
}