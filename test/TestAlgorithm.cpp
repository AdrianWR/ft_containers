#include <gtest/gtest.h>

#include "algorithm.hpp"
#include <algorithm>
#include <deque>
#include <map>
#include <string>
#include <vector>

bool pred_int(int a, int b) { return a == b; }
bool pred_string(std::string a, std::string b) { return a == b; }
bool pred_map(std::pair<int, int> a, std::pair<int, int> b) { return a == b; }

// Tests ft::equal

TEST(TestEqual, TestEqualTrue) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  std::vector<std::string> v3 = {"1", "2", "3", "4", "5"};
  std::vector<std::string> v4 = {"1", "2", "3", "4", "5"};
  std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_TRUE(ft::equal(v1.rbegin(), v1.rend(), v2.rbegin()));
  EXPECT_TRUE(ft::equal(v3.begin(), v3.end(), v4.begin()));
  EXPECT_TRUE(ft::equal(m1.begin(), m1.end(), m2.begin()));
}

TEST(TestEqual, TestEqualFalse) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 6};
  std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}};
  std::deque<int> d1 = {1, 2, 3, 4, 5};
  std::deque<int> d2 = {1, 2, 3, 4, 6};

  EXPECT_FALSE(ft::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_FALSE(ft::equal(v1.rbegin(), v1.rend(), v2.rbegin()));
  EXPECT_FALSE(ft::equal(m1.begin(), m1.end(), m2.begin()));
  EXPECT_FALSE(ft::equal(m1.rbegin(), m1.rend(), m2.rbegin()));
  EXPECT_FALSE(ft::equal(d1.begin(), d1.end(), d2.begin()));
}

TEST(TestEqual, TestEqualEmpty) {
  std::vector<int> v1;
  std::vector<int> v2;
  std::map<int, int> m1;
  std::map<int, int> m2;
  std::deque<int> d1;
  std::deque<int> d2;

  EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_TRUE(ft::equal(v1.rbegin(), v1.rend(), v2.rbegin()));
  EXPECT_TRUE(ft::equal(m1.begin(), m1.end(), m2.begin()));
  EXPECT_TRUE(ft::equal(m1.rbegin(), m1.rend(), m2.rbegin()));
  EXPECT_TRUE(ft::equal(d1.begin(), d1.end(), d2.begin()));
}

TEST(TestEqual, TestEqualPredicate) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  std::vector<std::string> v3 = {"1", "2", "3", "4", "5"};
  std::vector<std::string> v4 = {"1", "2", "3", "4", "5"};
  std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin(), pred_int));
  EXPECT_TRUE(ft::equal(v1.rbegin(), v1.rend(), v2.rbegin(), pred_int));
  EXPECT_TRUE(ft::equal(v3.begin(), v3.end(), v4.begin(), pred_string));
  EXPECT_TRUE(ft::equal(v3.rbegin(), v3.rend(), v4.rbegin(), pred_string));
  EXPECT_TRUE(ft::equal(m1.begin(), m1.end(), m2.begin(), pred_map));
  EXPECT_TRUE(ft::equal(m1.rbegin(), m1.rend(), m2.rbegin(), pred_map));
}

TEST(TestEqual, TestEqualDifferentContainers) {
  int v0[] = {1, 2, 3, 4, 5};
  std::vector<int> v1 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v0));
  EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v0, pred_int));
}

// Tests ft::lexicographical_compare

TEST(TestLexicographicalCompare, TestLexicographicalCompareEqual) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  std::vector<std::string> v3 = {"1", "2", "3", "4", "5"};
  std::vector<std::string> v4 = {"1", "2", "3", "4", "5"};
  std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_FALSE(
      ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
  EXPECT_FALSE(ft::lexicographical_compare(v1.rbegin(), v1.rend(), v2.rbegin(),
                                           v2.rend()));
}
