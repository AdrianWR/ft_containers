#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "vector.hpp"

TEST(TestVector, TestVectorDefaultConstructor) {
  ft::vector<int> v1;
  ft::vector<std::string> v2;
  ft::vector<float, std::allocator<float>> v3;

  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v2.size(), 0);
  ASSERT_EQ(v2.capacity(), 0);
  ASSERT_EQ(v3.size(), 0);
  ASSERT_EQ(v3.capacity(), 0);
}

TEST(TestVector, TestVectorFillConstructor) {
  ft::vector<int> v1(10);
  ft::vector<std::string> v2(10, "test");
  std::allocator<float> alloc;
  ft::vector<float, std::allocator<float>> v3(10, 1.0f, alloc);

  ASSERT_EQ(v1.size(), 10);
  ASSERT_EQ(v1.capacity(), 10);
  ASSERT_EQ(v1[0], 0);
  ASSERT_EQ(v1[9], 0);

  ASSERT_EQ(v2.size(), 10);
  ASSERT_EQ(v2.capacity(), 10);
  ASSERT_EQ(v2[0], "test");
  ASSERT_EQ(v2[9], "test");

  ASSERT_EQ(v3.size(), 10);
  ASSERT_EQ(v3.capacity(), 10);
  ASSERT_EQ(v3[0], 1.0f);
  ASSERT_EQ(v3[9], 1.0f);
}

TEST(TestVector, TestVectorRangeConstructor) {
  int arr1[] = {1, 2, 3, 4, 5};
  std::string arr2[] = {"one", "two", "three", "four", "five"};
  float arr3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<float, std::allocator<float>> v3(arr3, arr3 + 5);

  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), 5);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 3);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 5);

  ASSERT_EQ(v2.size(), 5);
  ASSERT_EQ(v2.capacity(), 5);
  ASSERT_EQ(v2[0], "one");
  ASSERT_EQ(v2[4], "five");

  ASSERT_EQ(v3.size(), 5);
  ASSERT_EQ(v3.capacity(), 5);
  ASSERT_FLOAT_EQ(v3[0], 1.0f);
  ASSERT_FLOAT_EQ(v3[4], 5.0f);
}

TEST(TestVector, TestVectorCopyConstructor) {
  int arr1[] = {1, 2, 3, 4, 5};
  std::string arr2[] = {"one", "two", "three", "four", "five"};
  float arr3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<float, std::allocator<float>> v3(arr3, arr3 + 5);

  ft::vector<int> v4(v1);
  ft::vector<std::string> v5(v2);
  ft::vector<float, std::allocator<float>> v6(v3);

  ASSERT_EQ(v4.size(), 5);
  ASSERT_EQ(v4.capacity(), 5);
  ASSERT_EQ(v4[0], 1);
  ASSERT_EQ(v4[1], 2);
  ASSERT_EQ(v4[2], 3);
  ASSERT_EQ(v4[3], 4);
  ASSERT_EQ(v4[4], 5);

  ASSERT_EQ(v5.size(), 5);
  ASSERT_EQ(v5.capacity(), 5);
  ASSERT_EQ(v5[0], "one");
  ASSERT_EQ(v5[4], "five");

  ASSERT_EQ(v6.size(), 5);
  ASSERT_EQ(v6.capacity(), 5);
  ASSERT_FLOAT_EQ(v6[0], 1.0f);
  ASSERT_FLOAT_EQ(v6[4], 5.0f);
}

TEST(TestVector, TestVectorDestructor) {
  // TODO
}

TEST(TestVector, TestVectorAssignmentOperator) {
  int arr1[] = {1, 2, 3, 4, 5};
  std::string arr2[] = {"one", "two", "three", "four", "five"};
  float arr3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<float, std::allocator<float>> v3(arr3, arr3 + 5);

  ft::vector<int> v4;
  ft::vector<std::string> v5;
  ft::vector<float, std::allocator<float>> v6;

  v4 = v1;
  // v5 = v2;
  v6 = v3;

  ASSERT_EQ(v4.size(), 5);
  ASSERT_EQ(v4.capacity(), 5);
  ASSERT_EQ(v4[0], 1);
  ASSERT_EQ(v4[1], 2);
  ASSERT_EQ(v4[2], 3);
  ASSERT_EQ(v4[3], 4);
  ASSERT_EQ(v4[4], 5);

  // ASSERT_EQ(v5.size(), 5);
  // ASSERT_EQ(v5.capacity(), 5);
  // ASSERT_EQ(v5[0], "one");
  // ASSERT_EQ(v5[4], "five");

  // ASSERT_EQ(v6.size(), 5);
  // ASSERT_EQ(v6.capacity(), 5);
  // ASSERT_FLOAT_EQ(v6[0], 1.0f);
  // ASSERT_FLOAT_EQ(v6[4], 5.0f);
}
