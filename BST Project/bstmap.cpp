// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Ayesha Mahmood ayeshm3@uw.edu
// 16 April 2023
#include "bstmap.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { this->copyHelper(bst.root); }
// copy tree helper method
void BSTMap::copyHelper(Node *root) {
  // Base Case
  if (root == nullptr) {
    return;
  }
  // Inserting root data
  this->insert(root->data);
  // Copying left subtree
  if (root->left != nullptr) {
    copyHelper(root->left);
  }
  // Copy right subtree
  if (root->right != nullptr) {
    copyHelper(root->right);
  }
}

// helper for building tree using a vector
BSTMap::Node *BSTMap::buildTreeHelper(const vector<value_type> &v,
                                      const int &firstIndex,
                                      const int &lastIndex) {

  // Base case
  if (firstIndex > lastIndex) {
    return NULL;
  }

  // Making middle element as root
  int middleElem = firstIndex + (lastIndex - firstIndex) / 2;
  Node *root = makeNode(v[middleElem]);

  // recursively building left subtree
  root->left = buildTreeHelper(v, firstIndex, middleElem - 1);

  // recursively building right subtree
  root->right = buildTreeHelper(v, middleElem + 1, lastIndex);

  return root;
}
// function to help make node
BSTMap::Node *BSTMap::makeNode(const value_type &item) {
  auto *newNode = new Node();
  newNode->data = item;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}
// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  vector<value_type> newVector(v);
  sort(newVector.begin(), newVector.end(), sortByWeightHelper);
  root = buildTreeHelper(newVector, 0, static_cast<int>(newVector.size() - 1));
}

// sorter (helps sort by weight)
int BSTMap::sortByWeightHelper(value_type &a, value_type &b) {
  return static_cast<int>(a.second < b.second);
}

// destructor
BSTMap::~BSTMap() { clear(); }

// Post Order recursively destructing tree
void BSTMap::BSTPostOrderRecursiveDelete(Node *curr) {
  // Base case if root null
  if (curr == nullptr) {
    return;
  }
  // recursively destruct left subtree
  BSTPostOrderRecursiveDelete(curr->left);
  // recursively destruct rightsubtree
  BSTPostOrderRecursiveDelete(curr->right);
  // delete root
  delete curr;
}

// delete all nodes in tree
// calls bst post order delete function as helper to recursively destruct tree
// passes in root to destruct tree
// when done destroying sets root to null
void BSTMap::clear() {
  BSTPostOrderRecursiveDelete(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() { return true; }

// Number of nodes in BST
int BSTMap::size() const { return sizeHelper(this->root); }
// helper funtion for size
int BSTMap::sizeHelper(Node *root) const {
  // Base case if root nullptr
  // no node in tree
  if (root == nullptr) {
    return 0;
  }
  // declaration of int that will store left side count
  int lSide = sizeHelper(root->left);
  // declaration of int that will store right side count
  int rSide = sizeHelper(root->right);
  // +1 for node we currently at plus left subtree and right
  return 1 + lSide + rSide;
}
// true if item is in BST
bool BSTMap::contains(const key_type &key) const {

  return containsHelper(root, key);
}
// contains helper function that takes in root and key we are looking for
bool BSTMap::containsHelper(Node *root, const key_type &key) const {
  // as long as root not null (i.e tree not empty)
  if (root == nullptr) {
    return false;
  }
  // if current node data matches key we are looking for returns true
  if (key == root->data.first) {
    return true;
  }
  // checks if current node data is less than key if less than goes to right
  // (towards greater)

  if (key > root->data.first) {
    return containsHelper(root->right, key);

    // checks if current node data is greater than key if greater goes to left
    //  (towards smaller)
  }
  return containsHelper(root->left, key);

  // if current node data matches key we are looking for returns true
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {

  if (this->contains(k)) {
    return root->data.second;
  }
  value_type item = value_type(k, 0);
  return this->insert(item);
  assert(false && "operator[] has not been implemented");
}
// function to search for specific key
BSTMap::mapped_type &BSTMap::searchHelper(Node *root, const key_type &key) {
  // if key matches current node we on return the value
  if (root->data.first == key) {
    return root->data.second;
  }
  // if key is greater than curren node we on
  // recursively call searchHelper on left side of tree
  if (root->data.first > key) {
    return searchHelper(root->left, key);
  }
  // if key is smalller than current node we on
  //  recursivelu call search on right side of tree

  return searchHelper(root->right, key);
}
// inserting with maintaining BST properties
BSTMap::mapped_type &BSTMap::insert(const value_type &item) {
  // if root is null just add to root
  if (root == nullptr) {
    root = makeNode(item);
    return root->data.second;
  }
  // else we make newNode and call recursive insert helper function to find
  // appropriate place to place it in tree

  Node *newNode = recursiveInsertHelper(root, item);
  return newNode->data.second;
}

// recursive insert helper function
BSTMap::Node *BSTMap::recursiveInsertHelper(Node *root,
                                            const value_type &item) {
  // if current node is less than item we are inserting and if to the right is
  // empty then add node there or else call recursive insert
  // helper on right side
  if (root->data < item) {
    if (root->right == nullptr) {
      Node *nodeToInsert = makeNode(item);

      root->right = nodeToInsert;
      root = root->right;

    } else {
      return recursiveInsertHelper(root->right, item);
    }
    // if current node is greater than item we are insering and if to the left
    // is empty then add node there or else call recursive insert
    // helper on left side
  } else if (root->data > item) {
    if (root->left == nullptr) {
      Node *nodeToInsert = makeNode(item);

      root->left = nodeToInsert;
      root = root->left;

    } else {
      return recursiveInsertHelper(root->left, item);
    }
  }
  return root;
}
// getAll to get all phrase as vector that match given prefix
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(v, root, k);

  return v;
}
// helper function for getAll
void BSTMap::getAllHelper(vector<value_type> &v, Node *root,
                          const key_type &k) const {
  // Base Case
  if (root == nullptr) {
    return;
  }
  // string that holds current prefix at root
  string targetPrefix = root->data.first.substr(0, k.length());
  // if current prefix of current node we on is less than key we looking for
  if (targetPrefix < k) {
    // recursively go to right
    getAllHelper(v, root->right, k);
  }
  // if current prefix of current node we at root is greater than key we looking
  // for
  if (targetPrefix > k) {
    // recursively go to left
    getAllHelper(v, root->left, k);
  }
  // if current prefix of current node we at is equal to key we are looking for
  if (targetPrefix == k) {
    // push it to vector
    v.push_back(root->data);
    // recursively call getAllHelper on right and left to continue adding more
    // matching prefix to vector
    getAllHelper(v, root->right, k);
    getAllHelper(v, root->left, k);
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  return 1 + static_cast<int>(max(getHeight(n->left), getHeight(n->right)));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  if (containsHelper(root, k)) {
    return 1;
  }

  return 0;
}
// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inOrderHelper(root, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preOrderHelper(root, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postOrderHelper(root, visit);
}
// helper function for in order
void BSTMap::inOrderHelper(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  inOrderHelper(n->left, visit);
  visit(n->data);

  inOrderHelper(n->right, visit);
}
// helper function for preorder
void BSTMap::preOrderHelper(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  visit(n->data);
  preOrderHelper(n->left, visit);
  preOrderHelper(n->right, visit);
}
// helper function for postorder
void BSTMap::postOrderHelper(Node *n,
                             void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  postOrderHelper(n->left, visit);
  postOrderHelper(n->right, visit);
  visit(n->data);
}
// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> v;
  addToVector(root, v);
  clear();
  root = buildTreeHelper(v, 0, static_cast<int>(v.size() - 1));
}
// Helper for adding to vector
void BSTMap::addToVector(Node *root, vector<value_type> &v) const {
  // Base case
  if (root == nullptr) {
    return;
  }
  addToVector(root->left, v);
  v.push_back(root->data);
  addToVector(root->right, v);
}
// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return sameSame(this->root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !sameSame(this->root, other.root);
}
// bool function to see if tree are identical
// takes root of of both tree as parameters
bool BSTMap::sameSame(Node *root, Node *otherRoot) const {
  // Base case
  // if both empty tree are identical
  if (root == nullptr && otherRoot == nullptr) {
    return true;
  }
  // if one empty other not then not identical
  if (root == nullptr || otherRoot == nullptr) {
    return false;
  }
  // if the root data is not equal  then not identical
  if (root->data != otherRoot->data) {
    return false;
  }
  // recursively call identical function on left subtrees and right subtrees to
  // coompare both
  //  to see if identical
  return sameSame(root->left, otherRoot->left) &&
         sameSame(root->right, otherRoot->right);
}

// function to find the in order sucessor
// will be helper for delete functions case of  deleting node with 2 children
BSTMap::Node *BSTMap::getMinimumKey(Node *root) {
  Node *successor = nullptr;
  Node *parent = nullptr;
  Node *current = root->right;
  // if node has a right child then inorder successor is the left node
  // it will follow left child pointer (starting from right ) till it reaches
  // the leaf node which will be the inorder sucesssor
  while (current != nullptr) {
    parent = successor;
    successor = current;
    current = current->left;
  }
  // if node doesn't have right child
  // we go back to find ancestor of node which is
  // left child of parent(which will become inorder sucessor)
  if (successor != root->right) {
    parent->left = successor->right;
    successor->right = root->right;
  }
  return successor;
}
// Bonus extra credit
// function that returns
bool BSTMap::remove(const key_type &k) {
  Node *parent = nullptr;
  Node *current = root;
  // setting bool to done to accurately passes assert test wheter removed or not
  bool done = false;
  // first we iterate through while loop to find node to delete
  while (current != nullptr && current->data.first != k) {
    parent = current;
    if (current->data.first > k) {
      current = current->left;
      done = true;
    } else {
      current = current->right;
      done = false;
    }
  }

  // base case empty tree
  if (current == nullptr) {
    return false;
  }
  // 1-leaf node case if only one child
  Node *child = nullptr;
  // when it has right child only
  if (current->left == nullptr) {
    child = current->right;
    // when it has left child only
  } else if (current->right == nullptr) {
    child = current->left;
  } else {
    // case when it has two children
    // finds in order sucessor to be removed
    // then replaces the data in node which is removed with data in order
    // succesor,

    Node *successor = getMinimumKey(current->right);
    if (current == this->root) {
      this->root = successor;
    } else if (done) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }
    successor->left = current->left;
    child = current->right;
  }

  if (current == this->root) {
    this->root = child;
  } else if (done) {
    parent->left = child;
  } else {
    parent->right = child;
  }

  delete current;
  current = nullptr;
  return true;
}
