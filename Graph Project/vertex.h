#ifndef VERTEX_H
#define VERTEX_H
#include "edge.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
// forward declaration
class Edge;
// Class Declaration
class Vertex {
  // making edge and graph friend class of vertex
  friend class Edge;
  friend class Graph;

public:
  // default constructor
  Vertex();

  // destructor
  // will help in destroying vertex object and edge objects  in its vector of
  // edge pointers
  ~Vertex();

  // copy constructor creatubg a new vertex as copy of current one
  Vertex(const Vertex &vertex);

  // constructor with name will create vertex with given label
  explicit Vertex(const string &label);
  // Moving is not allowed
  Vertex(Vertex &&other) = delete;

  // Assigment is not allowed
  Vertex &operator=(const Vertex &other) = delete;

  // Moving assignment is not allowed
  Vertex &operator=(Vertex &&other) = delete;

  // returns bool true or false depending on if edge is present
  // takes pointer to vertex objects to check if edge presenr
  bool searchEdge(Vertex *edgeToFind);

  // this functions helps to add edge to vector consisting oF edges.
  // after succcesful addition returns true
  // else returns false
  bool addEdge(Edge *edgeToAdd);

private:
  // vector of edges objects
  vector<Edge *> edges;
  // intializing label string for name of Vertex
  string label;
};

#endif
