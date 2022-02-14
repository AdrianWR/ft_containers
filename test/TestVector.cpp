#include <gtest/gtest.h>

#include "vector.hpp"

TEST(TestVector, TestVector) {
  ft::vector<int> v1;
  EXPECT_EQ(v1.size(), 0);
}
