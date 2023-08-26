// Ayesha Mahmood ayeshm3@uw.edu
// 16 April 2023
#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}
void test_ayeshm3_01() {
  cout << "Starting AC test_ayeshm3_01" << endl;
  cout << "* Testing myfile autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("appl");
  assert(v.size() == 7);
  assert(v[0].first == "apply");
  assert(v[0].second == 4494350);
  assert(v[1].first == "applicable");
  assert(v[1].second == 3205200);
  assert(v[2].first == "application");
  assert(v[2].second == 2654250);
  assert(v[3].first == "apple");
  assert(v[3].second == 1484010);
  assert(v[4].first == "applause");
  assert(v[4].second == 1417390);
  assert(v[5].first == "applying");
  assert(v[5].second == 676815);
  assert(v[6].first == "applications");
  assert(v[6].second == 442165);
  cout << "Ending test_ayeshm3_01" << endl;
}
void test_ayeshm3_02() {
  cout << "Starting AC test_ayeshm3_01" << endl;
  cout << "* Testing myfile autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("myFile2.txt");
  cout << "Ending test_ayeshm3_02" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  test_ayeshm3_01();
  test_ayeshm3_02();

  // TODO(student) Add more tests
}