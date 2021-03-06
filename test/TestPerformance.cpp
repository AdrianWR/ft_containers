#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <gtest/gtest.h>

const int kNumIterations = 100000;

TEST(TestPerformance, TestVector) {
  ft::vector<int> v;
  for (int i = 0; i < kNumIterations; i++)
    v.push_back(i);
  for (int i = 0; i < kNumIterations; i++)
    v.pop_back();
}

TEST(TestPerformance, TestVectorErase) {
  ft::vector<int> v;
  for (int i = 0; i < kNumIterations; i++)
    v.push_back(i);
  v.erase(v.begin(), v.end());
}

TEST(TestPerformance, TestMap) {
  ft::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
}

TEST(TestPerformance, TestMapErase) {
  ft::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
  ft::map<int, int>::iterator it = m.begin();
  it++;
  m.erase(it, m.end());
}

TEST(TestPerformance, TestMapFind) {
  ft::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
  m.find(1);
}

TEST(TestPerformance, TestStack) {
  ft::stack<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.push(i);
  for (int i = 0; i < kNumIterations; i++)
    s.pop();
}

TEST(TestPerformance, TestSet) {
  ft::set<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.insert(i);
}

TEST(TestPerformance, TestSetErase) {
  ft::set<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.insert(i);
  ft::set<int>::iterator it = s.begin();
  it++;
  s.erase(it, s.end());
}
