#include "graph.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  this->directionalEdges = directionalEdges;
}

// destructor iterates thru map
// and it deletes all values
Graph::~Graph() {
  for (const auto &iterator : graph) {
    delete iterator.second;
  }
  // for deleting anything else left after deleting value
  graph.clear();
}

// @return total number of vertices
int Graph::verticesSize() const { return static_cast<int>(graph.size()); }

// @return total number of edges
int Graph::edgesSize() const {
  int numberOfEdges = 0;
  for (const auto &iterator : graph) {
    numberOfEdges += static_cast<int>(iterator.second->edges.size());
  }
  return numberOfEdges;
}

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  while (graph.find(label) != graph.end()) {
    return static_cast<int>(graph.find(label)->second->edges.size());
  }
  return -1;
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
  // base case if already contains label return false
  if (this->contains(label)) {
    return false;
  }
  // otherwise it adds the new vetex into the graph using the label as key
  // then returns 0 as true to denote successful insertion
  graph.insert({label, new Vertex(label)});
  return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return graph.find(label) != graph.end();
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const {
  auto iterator = graph.find(label);
  string answer;

  if (iterator != graph.end()) {
    map<string, int> map = getEdgesHelper(label);
    int i = 0;
    for (auto iterator : map) {
      answer += iterator.first + "(" + to_string(iterator.second) + ")";
      i++;
      if (i < map.size()) {
        answer += ",";
      }
    }
  }
  return answer;
}
// helper
map<string, int> Graph::getEdgesHelper(const string &label) const {
  Vertex *vrtx = graph.find(label)->second;
  map<string, int> result;
  for (auto &edge : vrtx->edges) {
    string l = edge->endingPoint->label;
    int w = edge->weight;
    result.insert({l, w});
  }
  return result;
}

// @return true if successfully connected
bool Graph::connect(const string &startingPoint, const string &endingPoint,
                    int weight) {
  // edge case is when beggining and ending point are same vertex , so it
  // returrns false(cause empty)
  if (startingPoint == endingPoint) {
    return false;
  }
  // if ending point doesn't exist , creates ending point
  if (graph.find(endingPoint) == graph.end()) {
    add(endingPoint);
  }
  // if starting point does not exist creates starting point
  if (graph.find(startingPoint) == graph.end()) {
    add(startingPoint);
  }

  Vertex *vstartingPoint = graph.find(startingPoint)->second;
  Vertex *vendingPoint = graph.find(endingPoint)->second;
  // if it is directional , and  if there is edge that exists already then false
  if ((directionalEdges) && (vstartingPoint->searchEdge(vendingPoint))) {
    return false;
  }
  // else create an edge between them
  auto *edgeToAdd = new Edge(vstartingPoint, vendingPoint, weight);

  // for non directional graph
  //  if it is not directional  and  edge that is not there already existing in
  //  both both directions
  if (!directionalEdges && !vendingPoint->searchEdge(vstartingPoint)) {
    // created edge with specified ending and starting point , as well as
    // specified weight
    vendingPoint->addEdge(new Edge(vendingPoint, vstartingPoint, weight));
  }
  // then creates another edge in opposite direction
  return vstartingPoint->addEdge(edgeToAdd);
}

// function to disconnect the edges
bool Graph::disconnect(const string &startingPoint, const string &endingPoint) {
  // to check if both starting point and ending point present in graph
  // graph.find search for the vertex and returns iterator to the found elem
  if (graph.find(startingPoint) == graph.end() ||
      graph.find(endingPoint) == graph.end()) {
    return false;
  }
  // to check if the edge exists
  Vertex *vstartingPoint = graph.find(startingPoint)->second;
  Vertex *vendingPoint = graph.find(endingPoint)->second;
  // case where it is directional edge
  if (directionalEdges) {
    // iterates and searches for edge between 2 vertex
    for (int i = 0; i < vstartingPoint->edges.size(); i++) {
      auto *directedEdge = vstartingPoint->edges[i];
      // if found removes it
      // then returns true
      if (directedEdge->startingPoint->label == startingPoint &&
          directedEdge->endingPoint->label == endingPoint) {
        delete directedEdge;
        vstartingPoint->edges.erase(vstartingPoint->edges.begin() + i);
        return true;
      }
    }
    return false;
  }
  // case where it is undirectional edge
  if (directionalEdges) {
    // iterates and searches for between the two vertices in reverse fashion
    for (int i = 0; i < vstartingPoint->edges.size(); i++) {
      // 2 pointer for iterating so can disconect edge in both direction
      auto *undirectedEdge = vstartingPoint->edges[i];
      auto *undirectedEdgeTwo = vendingPoint->edges[i];
      if (undirectedEdge->startingPoint->label == startingPoint &&
          undirectedEdge->endingPoint->label == endingPoint) {
        delete undirectedEdge;
        vstartingPoint->edges.erase(vstartingPoint->edges.begin() + i);
      } else if (undirectedEdgeTwo->endingPoint->label == endingPoint &&
                 undirectedEdgeTwo->startingPoint->label == startingPoint) {
        delete undirectedEdge;
        vendingPoint->edges.erase(vendingPoint->edges.begin() + i);
      }
      // after successful deletion
      return true;
    }
  }
  return false;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  // if startlabel = graph.end() menas empty nothing there
  //  so just return
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  // creating stack of string type
  stack<string> dfsStack;
  // pushing the start label to stack
  dfsStack.push(startLabel);
  // creating set for visited ones
  set<string> visited;
  // adding the startLabel to visited ones
  visited.insert(startLabel);
  // as long as stack not empty
  while (!dfsStack.empty()) {
    // making  top vertex popped each iteration till empty
    string u = dfsStack.top();
    dfsStack.pop();
    // popped one marked as visted
    visit(u);
    // then iterated thru all popped vertex edges in reverse order using reverse
    // iteration
    Vertex *poppedVertex = graph.find(u)->second;
    for (auto iterator = poppedVertex->edges.rbegin();
         iterator != poppedVertex->edges.rend(); iterator++) {
      // checks if edge not visited before
      if (visited.find((*iterator)->endingPoint->label) == visited.end()) {
        // push to stack and mart as visited
        dfsStack.push((*iterator)->endingPoint->label);
        visited.insert((*iterator)->endingPoint->label);
      }
    }
  }
}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  // if startlabel = graph.end() menas empty nothing there
  //  so just return
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  // creating a queue of string
  queue<string> queue;
  // pushing startlabel to queue
  queue.push(startLabel);
  // creating set of string for visted
  set<string> visited;
  // adding the start label we have to visited set
  visited.insert(startLabel);
  // while loop as long as queue is not empty
  while (!queue.empty()) {
    // variable "u" stores the front
    string u = queue.front();
    // each iteraton front gets dequeued
    queue.pop();
    // then visited
    visit(u);
    // the dequeued vertex are iterated over
    Vertex *poppedVertex = graph.find(u)->second;
    for (auto &iterator : poppedVertex->edges) {
      //  // checks if edge not visited before
      if (visited.find(iterator->endingPoint->label) == visited.end()) {
        // pushes it to quueue
        queue.push(iterator->endingPoint->label);
        // markes it visited in set for "visiteds"
        visited.insert(iterator->endingPoint->label);
      }
    }
  }
}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  // creating map of string and int that represents label for wighted directed
  // graph represnents label of starting vertex stores weight
  map<string, int> labels;
  // creating map represneting the previous vetrtex in shortest path
  // stores previous vertex
  map<string, string> previousVertex;
  if (graph.find(startLabel) == graph.end()) {
    return make_pair(labels, previousVertex);
  }
  // creating a priority queue of int and pointer to the vertex object
  priority_queue<pair<int, Vertex *>, vector<pair<int, Vertex *>>,
                 greater<pair<int, Vertex *>>>
      priorityQueue;
  // int refers to weight of vertex
  //  pointer represents the vertex object of the graph
  //  pushing the start label
  priorityQueue.push({0, graph.find(startLabel)->second});
  // label weight of starting vertex set to default 0 weught
  labels[startLabel] = 0;
  // iterating as long as priority queue not empty
  while (!priorityQueue.empty()) {
    // make the top poppedVertex pointer to vertex object
    Vertex *poppedVertex = priorityQueue.top().second;
    priorityQueue.pop();
    // iterates thru the popped oned
    for (auto &edge : poppedVertex->edges) {
      // new weight summmed for each edge  by taking sum of the weight of
      // current popped vertex plus the edge weight
      int nWeight = labels[poppedVertex->label] + edge->weight;
      int oWeight = INT_MAX;
      if (labels.find(edge->endingPoint->label) != labels.end()) {
        oWeight = labels[edge->endingPoint->label];
      }
      // if new weight is smaller than old which is current weight
      // then current weight is updated with the new weight
      // and the previous vertex map updated with the current vertex popped
      if (nWeight < oWeight) {
        labels[edge->endingPoint->label] = nWeight;
        previousVertex[edge->endingPoint->label] = poppedVertex->label;
        priorityQueue.push({nWeight, edge->endingPoint});
      }
    }
  } // each iteration smallest weight is removed from Priority queue
  labels.erase(startLabel);
  // its edges looked at
  return make_pair(labels, previousVertex);
}

// minimum spanning tree using Prim's algorithm
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &startingPoint,
                              const string &endingPoint, int weight)) const {
  // tests for edge case:
  // 1- if starting vertex is not present in  graph
  // 2- if its  directional
  // 3- if it is empty
  // then simply return -1

  if (graph.find(startLabel) == graph.end() || directionalEdges ||
      graph.count(startLabel) == 0) {
    return -1;
  }

  int result = 0;
  // initializing priority queue that will hold pair ints and pointer to edges
  using IE = pair<int, Edge *>;
  // int refers to the weight of edges
  // the pointer to edge refer to edges
  priority_queue<IE, vector<IE>, greater<IE>> q;
  // getting the starting vertex point
  Vertex *poppedVertex = graph.find(startLabel)->second;
  // set to keep track of visited ones
  set<string> set;
  // iterating through it
  for (auto &iterator : poppedVertex->edges) {
    // pushing its edge to the priority queue
    q.push({iterator->weight, iterator});
  }
  // as long as q not empty
  while (!q.empty()) {
    // pops top element from priority queue
    // makes top element priority
    IE curr = q.top();
    // pops top elem from prioriity queue(hassmallest weight)
    q.pop();
    // then stores weight of the edge and pointer to the edge
    int currWeight = curr.first;
    Edge *pointerToEdge = curr.second;
    // then gets label for the starting and ending vertices of edge
    string currEdgeFromLabel = pointerToEdge->startingPoint->label;
    string currEdgeToLabel = pointerToEdge->endingPoint->label;
    // adds it to set
    set.insert(currEdgeFromLabel);
    // if not in set adds it so set
    // also adds weight of the edge to result
    // then calls visit function that have label of start and end vertices and
    // weight of edge adding the end vertex edge to the priority queue
    if (set.find(currEdgeToLabel) == set.end()) {
      set.insert(currEdgeToLabel);
      result += currWeight;
      visit(currEdgeFromLabel, currEdgeToLabel, currWeight);
      for (auto &edge : graph.find(currEdgeToLabel)->second->edges) {
        if (set.find(edge->endingPoint->label) == set.end()) {
          q.push({edge->weight, edge});
        }
      }
    }
  } // returns total weight of Minimum spanning tree  after priority queuue
    // empty
  return result;
}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream myfile(filename);
  if (!myfile.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i) {
    myfile >> fromVertex >> toVertex >> weight;
    connect(fromVertex, toVertex, weight);
  }
  myfile.close();
  return true;
}
