#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
// Forward Declaration of Class vertex
class Vertex;
// Class Declaration
class Edge {
  friend class Vertex;
  friend class Graph;

public:
  // default constructor
  Edge();

  // constructor that takes in starting point and ending point of vertex , as
  // well as weight
  Edge(Vertex *startingPoint, Vertex *endingPoint, int weight);

  // destructor
  ~Edge();

  // can't make copy of edge
  Edge(const Edge &edge) = delete;

  // moving not allowed
  Edge(Edge &&other) = delete;

  // assignment is also not allowed
  Edge &operator=(const Edge &other) = delete;

  // move assignment not allowed
  Edge &operator=(Edge &&other) = delete;

private:
  // starting point as pointer to vertex object
  Vertex *startingPoint;
  // ending point as pointer to vertex object
  Vertex *endingPoint;
  // initializing weight value as int
  int weight;
};

#endif
