#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "vector.hpp"

ft::vector<int>::size_type init_capacity = 48;

TEST(TestVector, TestVectorDefaultConstructor) {
  ft::vector<int> v1;
  ft::vector<std::string> v2;
  ft::vector<float, std::allocator<float>> v3;

  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), init_capacity);
  ASSERT_EQ(v2.size(), 0);
  ASSERT_EQ(v2.capacity(), init_capacity);
  ASSERT_EQ(v3.size(), 0);
  ASSERT_EQ(v3.capacity(), init_capacity);
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

  int cap = std::max<int>(init_capacity, 5);
  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), cap);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 3);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 5);

  ASSERT_EQ(v2.size(), 5);
  ASSERT_EQ(v2.capacity(), cap);
  ASSERT_EQ(v2[0], "one");
  ASSERT_EQ(v2[4], "five");

  ASSERT_EQ(v3.size(), 5);
  ASSERT_EQ(v3.capacity(), cap);
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

  int cap = std::max<int>(init_capacity, 5);
  ASSERT_EQ(v4.size(), 5);
  ASSERT_EQ(v4.capacity(), cap);
  ASSERT_EQ(v4[0], 1);
  ASSERT_EQ(v4[1], 2);
  ASSERT_EQ(v4[2], 3);
  ASSERT_EQ(v4[3], 4);
  ASSERT_EQ(v4[4], 5);

  ASSERT_EQ(v5.size(), 5);
  ASSERT_EQ(v5.capacity(), cap);
  ASSERT_EQ(v5[0], "one");
  ASSERT_EQ(v5[4], "five");

  ASSERT_EQ(v6.size(), 5);
  ASSERT_EQ(v6.capacity(), cap);
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
  char arr1[] = {'a', 'b', 'c', 'd', 'e'};
  std::string arr2[] = {"one", "two", "three", "four", "five"};
  float arr3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

  ft::vector<char> v1(arr1, arr1 + 5);
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<float, std::allocator<float>> v3(arr3, arr3 + 5);

  ft::vector<char> v4;
  ft::vector<std::string> v5;
  ft::vector<float, std::allocator<float>> v6;

  v4 = v1;
  v5 = v2;
  v6 = v3;

  ASSERT_EQ(v4.size(), v1.size());
  ASSERT_EQ(v4.capacity(), v1.capacity());
  ASSERT_EQ(v4[0], 'a');
  ASSERT_EQ(v4[1], 'b');
  ASSERT_EQ(v4[2], 'c');
  ASSERT_EQ(v4[3], 'd');
  ASSERT_EQ(v4[4], 'e');

  ASSERT_EQ(v5.size(), v2.size());
  ASSERT_EQ(v5.capacity(), v2.capacity());
  ASSERT_EQ(v5[0], "one");
  ASSERT_EQ(v5[1], "two");
  ASSERT_EQ(v5[2], "three");
  ASSERT_EQ(v5[3], "four");
  ASSERT_EQ(v5[4], "five");

  ASSERT_EQ(v6.size(), v3.size());
  ASSERT_EQ(v6.capacity(), v3.capacity());
  ASSERT_FLOAT_EQ(v6[0], 1.0f);
  ASSERT_FLOAT_EQ(v6[4], 5.0f);

  v1 = v1;

  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), std::max<unsigned int>(init_capacity, 5));
  ASSERT_EQ(v1[0], 'a');
  ASSERT_EQ(v1[1], 'b');
  ASSERT_EQ(v1[2], 'c');
  ASSERT_EQ(v1[3], 'd');
  ASSERT_EQ(v1[4], 'e');

  ft::vector<int> v7;
  ft::vector<int> v8;
  v7 = v8;
  ASSERT_EQ(v7.size(), 0);
  ASSERT_EQ(v7.capacity(), init_capacity);
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

TEST(TestVector, TestVectorResize) {
  ft::vector<int> v0;
  ASSERT_EQ(v0.size(), 0);

  v0.resize(12);
  ASSERT_EQ(v0.size(), 12);
  ASSERT_EQ(v0[0], 0);

  v0.resize(0);
  ASSERT_EQ(v0.size(), 0);

  for (int i = 1; i < 10; ++i) {
    v0.push_back(i);
  }
  v0.resize(5);
  v0.resize(8, 100);
  v0.resize(12);
  ASSERT_EQ(v0.size(), 12);
  ASSERT_EQ(v0[0], 1);
  ASSERT_EQ(v0[1], 2);
  ASSERT_EQ(v0[2], 3);
  ASSERT_EQ(v0[3], 4);
  ASSERT_EQ(v0[4], 5);
  ASSERT_EQ(v0[5], 100);
  ASSERT_EQ(v0[6], 100);
  ASSERT_EQ(v0[7], 100);
  ASSERT_EQ(v0[8], 0);
  ASSERT_EQ(v0[9], 0);
  ASSERT_EQ(v0[10], 0);
  ASSERT_EQ(v0[11], 0);
}

TEST(TestVector, TestVectorCapacity) {
  ft::vector<int> v0;
  ASSERT_EQ(v0.capacity(), init_capacity);

  ft::vector<int> v1(5);
  ASSERT_EQ(v1.capacity(), 5);

  ft::vector<int> v2(12, 42);
  ASSERT_EQ(v2.capacity(), 12);

  v2.push_back(42);
  ASSERT_EQ(v2.capacity(), 24);
}

TEST(TestVector, TestEmpty) {
  ft::vector<int> v0;
  ASSERT_TRUE(v0.empty());

  ft::vector<int> v1(5);
  ASSERT_FALSE(v1.empty());

  ft::vector<int> v2(12, 42);
  ASSERT_FALSE(v2.empty());
}

TEST(TestVector, TestVectorReserve) {
  ft::vector<int> v0;
  ASSERT_EQ(v0.capacity(), init_capacity);

  v0.reserve(32);
  ASSERT_EQ(v0.capacity(), std::max<unsigned int>(32, init_capacity));

  ft::vector<int> v1(41);
  ASSERT_EQ(v1.capacity(), 41);
  v1.reserve(12);
  ASSERT_EQ(v1.capacity(), 41);
}

TEST(TestVector, TestVectorElementAccess) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  v1.reserve(56);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 3);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 5);

  v1[5] = 42;
  v1[6] = 43;
  v1[7] = 44;
  v1[8] = 45;
  ASSERT_EQ(v1[5], 42);
  ASSERT_EQ(v1[6], 43);
  ASSERT_EQ(v1[7], 44);
  ASSERT_EQ(v1[8], 45);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2[0], 1);
  ASSERT_EQ(v2[1], 2);
  ASSERT_EQ(v2[2], 3);
  ASSERT_EQ(v2[3], 4);
  ASSERT_EQ(v2[4], 5);

  ASSERT_EQ(v1.size(), 5);
}

TEST(TestVector, TestVectorAt) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
  ASSERT_EQ(v1.at(3), 4);
  ASSERT_EQ(v1.at(4), 5);
  ASSERT_THROW(v1.at(5), std::out_of_range);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2.at(0), 1);
  ASSERT_EQ(v2.at(1), 2);
  ASSERT_EQ(v2.at(2), 3);
  ASSERT_EQ(v2.at(3), 4);
  ASSERT_EQ(v2.at(4), 5);
  ASSERT_THROW(v2.at(5), std::out_of_range);
}

TEST(TestVector, TestVectorFront) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.front(), 1);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2.front(), 1);
}

TEST(TestVector, TestVectorBack) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.back(), 5);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2.back(), 5);
}
