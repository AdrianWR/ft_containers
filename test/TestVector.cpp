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
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);

  ft::vector<int> *v2 = new ft::vector<int>(v1);
  delete v2; // No memory leak; assert not possible
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
  v5 = v2;
  v6 = v3;

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
  ASSERT_EQ(v5[1], "two");
  ASSERT_EQ(v5[2], "three");
  ASSERT_EQ(v5[3], "four");
  ASSERT_EQ(v5[4], "five");

  ASSERT_EQ(v6.size(), 5);
  ASSERT_EQ(v6.capacity(), 5);
  ASSERT_FLOAT_EQ(v6[0], 1.0f);
  ASSERT_FLOAT_EQ(v6[4], 5.0f);

  v1 = v1;

  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), 5);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 3);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 5);

  ft::vector<int> v7;
  ft::vector<int> v8;
  v7 = v8;
  ASSERT_EQ(v7.size(), 0);
  ASSERT_EQ(v7.capacity(), 0);
}

TEST(TestVector, TestVectorBegin) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<int>::iterator it = v1.begin();
  ASSERT_EQ(it, &v1[0]);
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(it + 1, &v1[1]);

  std::string arr2[] = {"one", "two", "three", "four", "five"};
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<std::string>::iterator it2 = v2.begin();
  ASSERT_EQ(*(it + 1), 2);
  ASSERT_EQ(it2, &v2[0]);
  ASSERT_EQ(*it2, "one");

  int arr3[] = {1, 2, 3, 4, 5};
  ft::vector<int> const v3(arr3, arr3 + 5);
  ft::vector<int>::const_iterator cit = v3.begin();
  ASSERT_EQ(cit, &v3[0]);
  ASSERT_EQ(*cit, 1);
  ASSERT_EQ(cit + 1, &v3[1]);
  ASSERT_EQ(*(cit + 1), 2);

  ft::vector<unsigned int> v4;
  ft::vector<unsigned int>::iterator it4 = v4.begin();
  ASSERT_EQ(it4, v4.end());
}

TEST(TestVector, TestVectorEnd) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<int>::iterator it = v1.end();
  ASSERT_EQ(it, &v1[5]);
  ASSERT_EQ(*(it - 1), 5);
  ASSERT_EQ(it - 1, &v1[4]);

  std::string arr2[] = {"one", "two", "three", "four", "five"};
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<std::string>::iterator it2 = v2.end();
  ASSERT_EQ(*(it2 - 1), "five");
  ASSERT_EQ(it2, &v2[5]);
  ASSERT_EQ(*(it2 - 2), "four");

  int arr3[] = {1, 2, 3, 4, 5};
  ft::vector<int> const v3(arr3, arr3 + 5);
  ft::vector<int>::const_iterator cit = v3.end();
  ASSERT_EQ(cit, &v3[5]);
  ASSERT_EQ(*(cit - 1), 5);
  ASSERT_EQ(cit - 1, &v3[4]);
  ASSERT_EQ(*(cit - 2), 4);

  ft::vector<unsigned int> v4;
  ft::vector<unsigned int>::iterator it4 = v4.end();
  ASSERT_EQ(it4, v4.begin());
}

TEST(TestVector, TestVectorRBegin) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<int>::iterator it = v1.begin();
  ft::vector<int>::iterator eit = v1.end();
  ft::vector<int>::reverse_iterator rit = v1.rbegin();
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(*rit, *(eit - 1 - i));
    ASSERT_EQ(*rit, *(it + 4 - i));
    ++rit;
  }
}

TEST(TestVector, TestVectorREnd) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<int>::iterator it = v1.begin();
  ft::vector<int>::iterator eit = v1.end();
  ft::vector<int>::reverse_iterator ritb = v1.rbegin();
  ft::vector<int>::reverse_iterator rite = v1.rend();

  ASSERT_EQ(*(rite - 1), *it);
  unsigned int i = 0;
  for (ritb = v1.rbegin(); ritb != v1.rend(); ++ritb) {
    ASSERT_EQ(*ritb, v1[4 - i++]);
  }
}

TEST(TestVector, TestVectorSize) {

  ft::vector<int> v0;
  ASSERT_EQ(v0.size(), 0);

  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.size(), 5);

  ft::vector<int> v2(5);
  ASSERT_EQ(v2.size(), 5);
}

TEST(TestVector, TestVectorMaxSize) {
  std::allocator<int> alloc;
  ft::vector<int> v0(alloc);
  ASSERT_EQ(v0.max_size(), alloc.max_size());

  std::allocator<int> alloc2;
  ft::vector<int> v1(5, 42, alloc2);
  ASSERT_EQ(v1.max_size(), alloc2.max_size());
  ASSERT_LE(v1.size(), v1.max_size());
}
