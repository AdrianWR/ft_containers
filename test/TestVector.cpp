#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "vector.hpp"

ft::vector<int>::size_type init_capacity = 0;

TEST(TestVectorConstructors, TestVectorDefaultConstructor) {
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

TEST(TestVectorConstructors, TestVectorFillConstructor) {
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

TEST(TestVectorConstructors, TestVectorRangeConstructor) {
  int arr1[] = {1, 2, 3, 4, 5};
  std::string arr2[] = {"one", "two", "three", "four", "five"};
  float arr3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<std::string> v2(arr2, arr2 + 5);
  ft::vector<float, std::allocator<float>> v3(arr3, arr3 + 5);

  int cap = std::max<int>(init_capacity, 5);
  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), cap);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(v1[i], i + 1);
  }

  ASSERT_EQ(v2.size(), 5);
  ASSERT_EQ(v2.capacity(), cap);
  ASSERT_EQ(v2[0], "one");
  ASSERT_EQ(v2[4], "five");

  ASSERT_EQ(v3.size(), 5);
  ASSERT_EQ(v3.capacity(), cap);
  ASSERT_FLOAT_EQ(v3[0], 1.0f);
  ASSERT_FLOAT_EQ(v3[4], 5.0f);
}

TEST(TestVectorConstructors, TestVectorCopyConstructor) {
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

TEST(TestVectorDesctructor, TestVectorDestructor) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);

  ft::vector<int> *v2 = new ft::vector<int>(v1);
  delete v2; // No memory leak; assert not possible
}

TEST(TestVectorAssignementOperator, TestVectorAssignmentOperator) {
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
  for (int i = 0; i < v1.size(); ++i) {
    ASSERT_EQ(v4[i], v1[i]);
  }

  ASSERT_EQ(v5.size(), v2.size());
  ASSERT_EQ(v5.capacity(), v2.capacity());
  for (int i = 0; i < v2.size(); ++i) {
    ASSERT_EQ(v5[i], v2[i]);
  }

  ASSERT_EQ(v6.size(), v3.size());
  ASSERT_EQ(v6.capacity(), v3.capacity());
  for (int i = 0; i < v3.size(); ++i) {
    ASSERT_FLOAT_EQ(v6[i], v3[i]);
  }

  v1 = v1;
  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), std::max<unsigned int>(init_capacity, 5));
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(v1[i], i + 'a');
  }

  ft::vector<int> v7;
  ft::vector<int> v8;
  v7 = v8;
  ASSERT_EQ(v7.size(), 0);
}

TEST(TestVectorIterators, TestVectorBegin) {
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

TEST(TestVectorIterators, TestVectorEnd) {
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

TEST(TestVectorIterators, TestVectorRBegin) {
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

TEST(TestVectorIterators, TestVectorREnd) {
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

TEST(TestVectorCapacity, TestVectorSize) {

  ft::vector<int> v0;
  ASSERT_EQ(v0.size(), 0);

  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.size(), 5);

  ft::vector<int> v2(5);
  ASSERT_EQ(v2.size(), 5);
}

TEST(TestVectorCapacity, TestVectorMaxSize) {
  std::allocator<int> alloc;
  ft::vector<int> v0(alloc);
  ASSERT_EQ(v0.max_size(), alloc.max_size());

  std::allocator<int> alloc2;
  ft::vector<int> v1(5, 42, alloc2);
  ASSERT_EQ(v1.max_size(), alloc2.max_size());
  ASSERT_LE(v1.size(), v1.max_size());
}

TEST(TestVectorCapacity, TestVectorResize) {
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

TEST(TestVectorCapacity, TestVectorCapacity) {
  ft::vector<int> v0;
  ASSERT_EQ(v0.capacity(), init_capacity);

  ft::vector<int> v1(5);
  ASSERT_EQ(v1.capacity(), 5);

  ft::vector<int> v2(12, 42);
  ASSERT_EQ(v2.capacity(), 12);

  v2.push_back(42);
  ASSERT_EQ(v2.capacity(), 24);
}

TEST(TestVectorCapacity, TestEmpty) {
  ft::vector<int> v0;
  ASSERT_TRUE(v0.empty());

  ft::vector<int> v1(5);
  ASSERT_FALSE(v1.empty());

  ft::vector<int> v2(12, 42);
  ASSERT_FALSE(v2.empty());
}

TEST(TestVectorCapacity, TestVectorReserve) {
  ft::vector<int> v0;
  ASSERT_EQ(v0.capacity(), init_capacity);

  v0.reserve(32);
  ASSERT_EQ(v0.capacity(), std::max<unsigned int>(32, init_capacity));

  ft::vector<int> v1(41);
  ASSERT_EQ(v1.capacity(), 41);
  v1.reserve(12);
  ASSERT_EQ(v1.capacity(), 41);
}

TEST(TestVectorElementAccess, TestVectorElementAccess) {
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

TEST(TestVectorElementAccess, TestVectorAt) {
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

TEST(TestVectorElementAccess, TestVectorFront) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.front(), 1);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2.front(), 1);
}

TEST(TestVectorElementAccess, TestVectorBack) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ASSERT_EQ(v1.back(), 5);

  ft::vector<int> const v2(arr1, arr1 + 5);
  ASSERT_EQ(v2.back(), 5);
}

TEST(TestVectorModifiers, TestVectorAssign) {
  ft::vector<int> v1;
  ft::vector<int> v2;
  ft::vector<int> v3;

  v1.assign(7, 100);
  ASSERT_EQ(v1.size(), 7);
  for (int i = 0; i < 7; ++i) {
    ASSERT_EQ(v1[i], 100);
  }

  ft::vector<int>::iterator it = v1.begin() + 1;
  v2.assign(it, v1.end() - 1);
  ASSERT_EQ(v2.size(), 5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(v2[i], 100);
  }

  int myints[] = {1776, 7, 4};
  v3.assign(myints, myints + 3);
  ASSERT_EQ(v3.size(), 3);
  ASSERT_EQ(v3[0], 1776);
  ASSERT_EQ(v3[1], 7);
  ASSERT_EQ(v3[2], 4);
}

TEST(TestVectorModifiers, TestVectorPushBack) {
  ft::vector<int> v1;
  v1.push_back(42);
  ASSERT_EQ(v1.size(), 1);
  ASSERT_EQ(v1[0], 42);

  ft::vector<int> v2(5);
  v2.push_back(42);
  ASSERT_EQ(v2.size(), 6);
  ASSERT_EQ(v2[5], 42);

  ft::vector<int> v3(12, 42);
  v3.push_back(43);
  ASSERT_EQ(v3.size(), 13);
  ASSERT_EQ(v3[12], 43);
}

TEST(TestVectorModifiers, TestVectorPopBack) {
  ft::vector<int> v1;
  ASSERT_THROW(v1.pop_back(), std::out_of_range);

  ft::vector<int> v2(5);
  v2.pop_back();
  ASSERT_EQ(v2.size(), 4);

  ft::vector<int> v3(12, 42);
  v3.pop_back();
  ASSERT_EQ(v3.size(), 11);
}

TEST(TestVectorModifiers, TestVectorInsert) {
  ft::vector<int> v1(3, 100);
  ft::vector<int>::iterator it = v1.begin();

  it = v1.insert(it, 200);
  ASSERT_EQ(v1.size(), 4);
  ASSERT_EQ(v1[0], 200);
  ASSERT_EQ(v1[1], 100);
  ASSERT_EQ(v1[2], 100);
  ASSERT_EQ(v1[3], 100);

  v1.insert(it, 2, 300);
  ASSERT_EQ(v1.size(), 6);
  ASSERT_EQ(v1[0], 300);
  ASSERT_EQ(v1[1], 300);
  ASSERT_EQ(v1[2], 200);
  ASSERT_EQ(v1[3], 100);
  ASSERT_EQ(v1[4], 100);
  ASSERT_EQ(v1[5], 100);

  it = v1.begin();
  ft::vector<int> v2(2, 400);
  v1.insert(it + 2, v2.begin(), v2.end());
  ASSERT_EQ(v1.size(), 8);
  ASSERT_EQ(v1[0], 300);
  ASSERT_EQ(v1[1], 300);
  ASSERT_EQ(v1[2], 400);
  ASSERT_EQ(v1[3], 400);
  ASSERT_EQ(v1[4], 200);
  ASSERT_EQ(v1[5], 100);
  ASSERT_EQ(v1[6], 100);
  ASSERT_EQ(v1[7], 100);

  int arr1[] = {501, 502, 503};
  v1.insert(v1.begin(), arr1, arr1 + 3);
  ASSERT_EQ(v1.size(), 11);
  ASSERT_EQ(v1[0], 501);
  ASSERT_EQ(v1[1], 502);
  ASSERT_EQ(v1[2], 503);
  ASSERT_EQ(v1[3], 300);
  ASSERT_EQ(v1[4], 300);
  ASSERT_EQ(v1[5], 400);
  ASSERT_EQ(v1[6], 400);
  ASSERT_EQ(v1[7], 200);
  ASSERT_EQ(v1[8], 100);
  ASSERT_EQ(v1[9], 100);
  ASSERT_EQ(v1[10], 100);

  ft::vector<int> v3(2, 500);
  v3.insert(v3.begin() + 1, 250);
  ASSERT_EQ(v3.size(), 3);
  ASSERT_EQ(v3[0], 500);
  ASSERT_EQ(v3[1], 250);
  ASSERT_EQ(v3[2], 500);
}

TEST(TestVectorModifiers, TestVectorErase) {
  int arr1[] = {1, 2, 3, 4, 5};
  ft::vector<int> v1(arr1, arr1 + 5);
  ft::vector<int>::iterator it = v1.begin();

  it = v1.erase(it + 2);
  ASSERT_EQ(v1.size(), 4);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 4);
  ASSERT_EQ(v1[3], 5);

  it = v1.begin();
  it = v1.erase(it + 1, v1.end());
  ASSERT_EQ(v1.size(), 1);
  ASSERT_EQ(v1[0], 1);

  ft::vector<int> v2(3, 200);
  it = v2.begin();
  it = v2.erase(it, it + 2);
  ASSERT_EQ(v2.size(), 1);
  ASSERT_EQ(v2[0], 200);

  ft::vector<int> v3(3, 300);
  it = v3.begin();
  it = v3.erase(it + 1);
  ASSERT_EQ(v3.size(), 2);
  ASSERT_EQ(v3[0], 300);
  ASSERT_EQ(v3[1], 300);
}

TEST(TestVectorModifiers, TestVectorSwap) {
  ft::vector<int> v1(3, 100);
  ft::vector<int> v2(5, 200);
  v1.swap(v2);
  ASSERT_EQ(v1.size(), 5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(v1[i], 200);
  }
  ASSERT_EQ(v2.size(), 3);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(v2[i], 100);
  }
}

TEST(TestVectorModifiers, TestVectorClear) {
  ft::vector<int> v1;

  v1.push_back(100);
  v1.push_back(200);
  v1.push_back(300);

  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1[0], 100);
  ASSERT_EQ(v1[1], 200);
  ASSERT_EQ(v1[2], 300);

  v1.clear();
  ASSERT_EQ(v1.size(), 0);

  v1.push_back(1101);
  v1.push_back(2202);
  ASSERT_EQ(v1[0], 1101);
  ASSERT_EQ(v1[1], 2202);
}

TEST(TestVectorGetAllocator, TestVectorGetAllocator) {
  ft::vector<int> v;
  int *p;
  unsigned int i;

  p = v.get_allocator().allocate(5);
  for (i = 0; i < 5; i++) {
    v.get_allocator().construct(&p[i], i);
  }
  for (i = 0; i < 5; i++) {
    ASSERT_EQ(p[i], i);
  }
  for (i = 0; i < 5; i++) {
    v.get_allocator().destroy(&p[i]);
  }
  v.get_allocator().deallocate(p, 5);
}

TEST(TestVectorNonMemberFunctions, TestVectorRelationalOperators) {
  ft::vector<int> v1(3, 100);
  ft::vector<int> v2(3, 100);
  ft::vector<int> v3(2, 200);
  ft::vector<int> v4(3, 300);
  ft::vector<int> v5(3, 400);

  ASSERT_TRUE(v1 == v2);
  ASSERT_FALSE(v1 == v3);
  ASSERT_FALSE(v1 == v4);
  ASSERT_FALSE(v1 == v5);

  ASSERT_FALSE(v1 != v2);
  ASSERT_TRUE(v1 != v3);
  ASSERT_TRUE(v1 != v4);
  ASSERT_TRUE(v1 != v5);

  ASSERT_FALSE(v1 < v2);
  ASSERT_TRUE(v1 < v3);
  ASSERT_TRUE(v1 < v4);
  ASSERT_TRUE(v1 < v5);

  ASSERT_TRUE(v1 <= v2);
  ASSERT_TRUE(v1 <= v3);
  ASSERT_TRUE(v1 <= v4);
  ASSERT_TRUE(v1 <= v5);

  ASSERT_FALSE(v1 > v2);
  ASSERT_FALSE(v1 > v3);
  ASSERT_FALSE(v1 > v4);
  ASSERT_FALSE(v1 > v5);

  ASSERT_TRUE(v1 >= v2);
  ASSERT_FALSE(v1 >= v3);
  ASSERT_FALSE(v1 >= v4);
  ASSERT_FALSE(v1 >= v5);
}

TEST(TestVectorNonMemberFunctions, TestVectorSwapOverload) {
  ft::vector<int> v1(3, 100);
  ft::vector<int> v2(5, 200);
  ft::swap(v1, v2);
  ASSERT_EQ(v1.size(), 5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(v1[i], 200);
  }
  ASSERT_EQ(v2.size(), 3);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(v2[i], 100);
  }
}
