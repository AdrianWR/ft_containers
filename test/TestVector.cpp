#include <gtest/gtest.h>

#include "Vector.hpp"

TEST(TestVector, TestVector) {
    ft::Vector<int> v1;
    EXPECT_EQ(v1.size(), 0);
}

