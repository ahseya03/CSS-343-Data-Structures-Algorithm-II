
// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */
// Ayesha Mahmood ayeshm3@uw.edu
// 16 April 2023

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}
// testing empty
void test_ayeshm3_04() {
  cout << "******TESTING FOR EMPTY*********" << endl;
  BSTMap b;
  assert(b.empty());
  cout << "SUCCESFULLY DONE TESTING FOR EMPTY" << endl;
}
// testing contains
void test_ayeshm3_05() {
  cout << "\n******TESTING FOR CONTAINS*********" << endl;
  BSTMap b;
  b["watermelon"] = 10;
  b["burgers"] = 21;
  assert(b.contains("watermelon") == true);
  assert(b.contains("burgers") == true);
  cout << "\tBST contains the items" << endl;
  cout << "******TESTING FOR NOT CONTAINS*********" << endl;
  assert(b.contains("icecream") == false);
  assert(b.contains("mango") == false);
  cout << "\tBST does not contain the items" << endl;

  cout << "SUCCESFULLY DONE TESTING FOR CONTAINS" << endl;
}
// testing for count either 0 or 1( not present )
void test_ayeshm3_06() {
  cout << "\n******TESTING FOR COUNT*********" << endl;
  BSTMap b;
  b["cookies"] = 2;
  assert(b.count("cookies") == 1);
  cout << "\tCount of item is 1" << endl;
  // clearing everything
  cout << "CLEARING EVERYTHING" << endl;
  b.clear();
  assert(b.count("cookies") == 0);
  cout << "Testing size";
  assert(b.size() == 0);

  cout << "\tNow count of previous item is 0 " << endl;
  cout << "SUCCESFULLY DONE TESTING FOR COUNT" << endl;
}
// testing for get all

void test_ayeshm3_07() {

  cout << "\n******TESTING FOR GET ALL*********" << endl;
  BSTMap b;
  b["potato"] = 7;
  b["popcorn"] = 5;
  b["pomegranate"] = 2;
  b["pizza"] = 87;
  b["pie"] = 12;
  cout << "Printing food items that start with 'po' " << endl;
  auto v = b.getAll("po");
  BSTMap foodList(v);
  cout << foodList;
}
// testing copy constructor
void test_ayeshm3_08() {
  cout << "TESTING COPY CONSTRUCTOR" << endl;

  BSTMap b1;
  b1["strawberry"] = 21;
  b1["cherry"] = 7;

  BSTMap b2(b1);
  cout << "\t Testing..." << endl;
  cout << b2 << endl;
  assert(b2 == b1);
  cout << "SUCCESSFULLY PASSED COPY CONSTRUCTOR TEST\n" << endl;
}
// testing remove function
void test_ayeshm3_09() {
  cout << "TESTING REMOVE FUNCTION" << endl;
  BSTMap b;
  b["10"] = 0;
  b["22"] = 1;
  b["33"] = 2;
  b["43"] = 3;
  b["54"] = 4;
  assert(b.size() == 5);
  cout << b << endl;
  assert(b.remove("10") == true);
  cout << b << endl;
  assert(b.remove("10") == false);
  assert(b.size() == 4);
  assert(b.remove("22") == true);
  assert(b.remove("33") == true);
  assert(b.remove("43") == true);
  assert(b.remove("54") == true);
  cout << b << endl;
  assert(b.size() == 0);
  cout << "SUCCESSFULLY PASSED COPY CONSTRUCTOR TEST\n" << endl;
}

// // Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test_ayeshm3_04();
  test_ayeshm3_05();
  test_ayeshm3_06();
  test_ayeshm3_07();
  test_ayeshm3_08();
  test_ayeshm3_09();

  // TODO(student) Add more tests
}