#include "stack.hpp"
#include "vector.hpp"
#include <gtest/gtest.h>
#include <list>
#include <vector>

TEST(TestStack, TestConstructor) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
}

TEST(TestStack, TestPush) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  s.push(42);
  s1.push(42);
  s2.push(42);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s1.size(), 11);
  ASSERT_EQ(s2.size(), 11);
}

TEST(TestStack, TestTop) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  s.push(43);
  s1.push(43);
  s2.push(43);
  ASSERT_EQ(s.top(), 43);
  ASSERT_EQ(s1.top(), 43);
  ASSERT_EQ(s2.top(), 43);
}

TEST(TestStack, TestPop) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  s.push(43);
  s1.push(43);
  s2.push(43);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s1.size(), 11);
  ASSERT_EQ(s2.size(), 11);
  s.pop();
  s1.pop();
  s2.pop();
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
}

TEST(TestStack, TestEmpty) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  ASSERT_TRUE(s.empty());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s2.empty());
}

TEST(TestStack, TestSize) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  std::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, std::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  s.push(43);
  s1.push(43);
  s2.push(43);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s1.size(), 11);
  ASSERT_EQ(s2.size(), 11);
  s.pop();
  s1.pop();
  s2.pop();
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
}

TEST(TestStack, TestComparisonOperators) {
  ft::vector<int> v;
  ft::vector<int> v1(10, 42);
  ft::vector<int> v2(10, 42);

  ft::stack<int> s(v);
  ft::stack<int> s1(v1);
  ft::stack<int, ft::vector<int>> s2(v2);
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  ASSERT_TRUE(s == s);
  ASSERT_FALSE(s != s);
  ASSERT_FALSE(s == s1);
  ASSERT_TRUE(s != s1);
  ASSERT_FALSE(s == s2);
  ASSERT_TRUE(s != s2);
  s.push(43);
  s1.push(43);
  s2.push(43);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s1.size(), 11);
  ASSERT_EQ(s2.size(), 11);
  ASSERT_TRUE(s == s);
  ASSERT_FALSE(s != s);
  ASSERT_FALSE(s == s1);
  ASSERT_TRUE(s != s1);
  ASSERT_FALSE(s == s2);
  ASSERT_TRUE(s != s2);
  s.pop();
  s1.pop();
  s2.pop();
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s1.size(), 10);
  ASSERT_EQ(s2.size(), 10);
  ASSERT_TRUE(s == s);
  ASSERT_FALSE(s != s);
  ASSERT_FALSE(s == s1);
  ASSERT_TRUE(s != s1);
  ASSERT_FALSE(s == s2);
  ASSERT_TRUE(s != s2);
}
