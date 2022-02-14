#include <gtest/gtest.h>

#include "Vector.hpp"

TEST(TestVector, TestVector) {
  ft::vector<int> v1;
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(1, 0);
}
