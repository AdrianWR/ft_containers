#include "map.hpp"
#include "vector.hpp"
#include <gtest/gtest.h>
#include <map.hpp>
#include <vector.hpp>

TEST(TestPerformance, TestVector) {
  ft::vector<int> v;
  for (int i = 0; i < 1000000; i++)
    v.push_back(i);
  for (int i = 0; i < 1000000; i++)
    v.pop_back();
}

TEST(TestPerformanceSTL, TestVector) {
  std::vector<int> v;
  for (int i = 0; i < 1000000; i++)
    v.push_back(i);
  for (int i = 0; i < 1000000; i++)
    v.pop_back();
}

TEST(TestPerformance, TestMap) {
  ft::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
}

TEST(TestPerformanceSTL, TestMap) {
  std::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
}

TEST(TestPerformance, TestMapErase) {
  ft::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
  ft::map<int, int>::iterator it = m.begin();
  it++;
  // m.erase(it, m.end());
}

TEST(TestPerformanceSTL, TestMapErase) {
  std::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
  std::map<int, int>::iterator it = m.begin();
  it++;
  m.erase(it, m.end());
}
