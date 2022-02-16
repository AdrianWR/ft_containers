#include <gtest/gtest.h>

#include "algorithm.hpp"
#include <algorithm>
#include <map>
#include <vector>

class TestEqual : public ::testing::Test {
protected:
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  std::vector<int> v3 = {1, 2, 3, 4, 6};
  std::vector<int> v4 = {1, 2, 3, 4, 5, 6};
  std::vector<int> v5 = {};

  std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}};
};

TEST_F(TestEqual, TestEqualSimpleIterator) {
  EXPECT_TRUE(std::equal(v1.begin(), v1.end(), v2.begin()) ==
              ft::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_TRUE(std::equal(v1.rbegin(), v1.rend(), v2.rbegin()) ==
              ft::equal(v1.rbegin(), v1.rend(), v2.rbegin()));
  EXPECT_TRUE(std::equal(m1.begin(), m1.end(), m2.begin()) ==
              ft::equal(m1.begin(), m1.end(), m2.begin()));
  EXPECT_TRUE(std::equal(m1.rbegin(), m1.rend(), m2.rbegin()) ==
              ft::equal(m1.rbegin(), m1.rend(), m2.rbegin()));
}
