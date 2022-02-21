#include <gtest/gtest.h>
#include <string>

#include "utility.hpp"

TEST(TestPair, TestPairConstructor) {
  // Default constructor
  std::pair<int, std::string> p0;
  EXPECT_EQ(p0.first, 0);
  EXPECT_EQ(p0.second, "");

  // Initialization constructor
  ft::pair<int, int> p1(1, 2);
  EXPECT_EQ(p1.first, 1);
  EXPECT_EQ(p1.second, 2);

  ft::pair<double, std::string> p2(3.14, "pi");
  EXPECT_FLOAT_EQ(p2.first, 3.14);
  EXPECT_EQ(p2.second, "pi");

  ft::pair<std::string, std::string> p3("hello", "world");
  EXPECT_EQ(p3.first, "hello");
  EXPECT_EQ(p3.second, "world");

  // Copy constructor
  ft::pair<std::string, std::string> p4(p3);
  EXPECT_EQ(p4.first, "hello");
  EXPECT_EQ(p4.second, "world");
}

TEST(TestPair, TestPairAssignment) {
  ft::pair<int, int> p1(1, 2);
  ft::pair<int, int> p2(3, 4);
  p2 = p1;
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);

  ft::pair<int, int> p0;
  p0 = p1;
  EXPECT_EQ(p0.first, 1);
  EXPECT_EQ(p0.second, 2);

  ft::pair<double, std::string> p3(3.14, "pi");
  ft::pair<double, std::string> p4(2.71, "e");
  p4 = p3;
  EXPECT_FLOAT_EQ(p4.first, 3.14);
  EXPECT_EQ(p4.second, "pi");
}

TEST(TestPair, TestPairRelationalOperators) {
  ft::pair<int, int> p1(1, 2);
  ft::pair<int, int> p2(3, 4);
  ft::pair<int, int> p3(1, 2);
  ft::pair<int, int> p4(1, 3);
  ft::pair<int, int> p5(2, 2);
  ft::pair<int, int> p6(2, 6);

  EXPECT_TRUE(p1 == p3);
  EXPECT_TRUE(p1 != p2);
  EXPECT_FALSE(p1 == p4);
  EXPECT_TRUE(p1 < p2);
  EXPECT_TRUE(p4 > p1);
  EXPECT_TRUE(p1 <= p3);
  EXPECT_TRUE(p2 > p6);
  EXPECT_TRUE(p6 >= p5);
}

TEST(TestMakePair, TestMakePair) {
  ft::pair<int, int> p0;
  p0 = ft::make_pair(1, 2);
  EXPECT_EQ(p0.first, 1);
  EXPECT_EQ(p0.second, 2);

  ft::pair<int, int> p1 = ft::make_pair(1, 2);
  EXPECT_EQ(p1.first, 1);
  EXPECT_EQ(p1.second, 2);

  ft::pair<double, std::string> p2 = ft::make_pair(3.14, "pi");
  EXPECT_FLOAT_EQ(p2.first, 3.14);
  EXPECT_EQ(p2.second, "pi");

  ft::pair<std::string, std::string> p3 = ft::make_pair("hello", "world");
  EXPECT_EQ(p3.first, "hello");
  EXPECT_EQ(p3.second, "world");
}
