#include <gtest/gtest.h>
#include <map>
#include <set>
#include <stack>
#include <vector>

const int kNumIterations = 100000;

TEST(TestPerformanceSTL, TestVector) {
  std::vector<int> v;
  for (int i = 0; i < kNumIterations; i++)
    v.push_back(i);
  for (int i = 0; i < kNumIterations; i++)
    v.pop_back();
}

TEST(TestPerformanceSTL, TestVectorErase) {
  std::vector<int> v;
  for (int i = 0; i < kNumIterations; i++)
    v.push_back(i);
  v.erase(v.begin(), v.end());
}

TEST(TestPerformanceSTL, TestMap) {
  std::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
}

TEST(TestPerformanceSTL, TestMapErase) {
  std::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
  std::map<int, int>::iterator it = m.begin();
  it++;
  m.erase(it, m.end());
}

TEST(TestPerformanceSTL, TestMapFind) {
  std::map<int, int> m;
  for (int i = 0; i < kNumIterations; i++)
    m[i] = i;
  (void)m.find(1);
}

TEST(TestPerformanceSTL, TestStack) {
  std::stack<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.push(i);
  for (int i = 0; i < kNumIterations; i++)
    s.pop();
}

TEST(TestPerformanceSTL, TestSet) {
  std::set<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.insert(i);
}

TEST(TestPerformanceSTL, TestSetErase) {
  std::set<int> s;
  for (int i = 0; i < kNumIterations; i++)
    s.insert(i);
  std::set<int>::iterator it = s.begin();
  it++;
  s.erase(it, s.end());
}
