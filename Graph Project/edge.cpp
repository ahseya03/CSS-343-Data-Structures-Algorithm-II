#include "edge.h"
using namespace std;
// Edge default constructor that has default starting point of edge, ending
// point, and default weight set to 0
Edge::Edge() {
  this->startingPoint = {};
  this->endingPoint = {};
  weight = 0;
}
// Parametrized Edge constructor that will takes pointer to starting Point and
// ending point  of Vertex object and also weight used for creating edge between
// vertices

Edge::Edge(Vertex *startingPoint, Vertex *endingPoint, int weight) {
  this->startingPoint = startingPoint;
  this->endingPoint = endingPoint;
  this->weight = weight;
}
// Destructor for Edge

Edge::~Edge() {}