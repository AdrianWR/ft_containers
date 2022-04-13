#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <gtest/gtest.h>
#include <map>
#include <stack>
#include <vector>

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
  m.erase(it, m.end());
}

TEST(TestPerformanceSTL, TestMapErase) {
  std::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
  std::map<int, int>::iterator it = m.begin();
  it++;
  m.erase(it, m.end());
}

TEST(TestPerformance, TestMapFind) {
  ft::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
  m.find(1);
}

TEST(TestPerformanceSTL, TestMapFind) {
  std::map<int, int> m;
  for (int i = 0; i < 1000000; i++)
    m[i] = i;
  (void)m.find(1);
}

TEST(TestPerformance, TestStack) {
  ft::stack<int> s;
  for (int i = 0; i < 1000000; i++)
    s.push(i);
  for (int i = 0; i < 1000000; i++)
    s.pop();
}

TEST(TestPerformanceSTL, TestStack) {
  std::stack<int> s;
  for (int i = 0; i < 1000000; i++)
    s.push(i);
  for (int i = 0; i < 1000000; i++)
    s.pop();
}
