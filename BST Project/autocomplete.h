#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

using namespace std;

class Autocomplete {
public:
  // Auto complete constructor()
  Autocomplete() = default;
  // void function that takes in file name to read
  void readFile(const string &fileName);
  // complete function returns vector with all key pair that match the prefix
  // passed in to function
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
