#include "vertex.h"
#include <string>
#include <vector>

using namespace std;

// default constructor
Vertex::Vertex() {}
// destructor
// uses iterator that iterates thru all edge and deletes them
Vertex::~Vertex() {

  for (auto *iterator : edges) {
    delete iterator;
  }
  edges.clear();
}

// copy constructor used for creating vertex object
// and then gives it its appropraiate label and edge
// const used  so that the vertex object doesn't get modified during copying
// process
// Vertex::Vertex(const Vertex &vertex) {
//   this->label = label;
//   this->edges = edges;
// }

// constructor that supports creation of new vertex with provided label
// also intitializes array of empty edges
Vertex::Vertex(const string &label) {
  this->label = label;
  this->edges = {};
}

// this function uses iterator to iterates over edges of vectore
// compares each edge's starting point and ending point with the "dge"passed in
// that we are looking for
//  if found returns 1(true ) else returns 0(false)
bool Vertex::searchEdge(Vertex *edgeToFind) {

  for (auto iterator = edges.begin(); iterator != edges.end(); ++iterator) {
    if ((*iterator)->startingPoint == this &&
        (*iterator)->endingPoint == edgeToFind) {
      return true;
    }
  }
  return false;
}
bool Vertex::addEdge(Edge *edgeToAdd) {
  // base case if vector of edge objects empty then simply add edge
  if (this->edges.empty()) {
    this->edges.push_back(edgeToAdd);
    return true;
  }
  // else we create iterator that iterates thry vector of edge objects
  // as long as its not reaches end and the edge we are trying to add the label
  // is greater or equal to the iterator it iterates
  //  if ending point  lavel of both the edge we trying to add and iterator
  //  ending point label is equal then return false
  // else keeping iteratiing till we find an appropriate place to add the edge
  auto iterator = this->edges.begin();
  while (iterator != this->edges.end() &&
         edgeToAdd->endingPoint->label >= (*iterator)->endingPoint->label) {
    if (edgeToAdd->endingPoint->label == (*iterator)->endingPoint->label) {
      return false;
    }
    iterator++;
  }

  this->edges.insert(iterator, edgeToAdd);
  return true;
}
