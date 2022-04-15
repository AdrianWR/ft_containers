#include <gtest/gtest.h>

#include "set.hpp"

TEST(TestSet, TestSetDefaultConstructor) {
  ft::set<int> s;
  ASSERT_EQ(s.size(), 0);
}

TEST(TestSet, TestSetRangeConstructor) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);
  ASSERT_EQ(s.size(), 5);
}

TEST(TestSet, TestSetCopyConstructor) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int> s2(s);
  ASSERT_EQ(s2.size(), 5);
  ASSERT_EQ(s2.count(1), 1);
}

TEST(TestSet, TestSetAssignmentOperator) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int> s2;
  s2 = s;
  ASSERT_EQ(s2.size(), 5);
  ASSERT_TRUE(s == s2);
}

TEST(TestSet, TestSetIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::iterator it = s.begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 3);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(it, s.end());

  ft::set<int> const sc(arr, arr + 5);

  ft::set<int>::const_iterator itc = sc.begin();
  ASSERT_EQ(*itc++, 1);
  ASSERT_EQ(*itc++, 2);
  ASSERT_EQ(*itc++, 3);
  ASSERT_EQ(*itc++, 4);
  ASSERT_EQ(*itc++, 5);
  ASSERT_EQ(itc, sc.end());
}

TEST(TestSet, TestSetReverseIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::reverse_iterator rit = s.rbegin();
  ASSERT_EQ(*rit++, 5);
  ASSERT_EQ(*rit++, 4);
  ASSERT_EQ(*rit++, 3);
  ASSERT_EQ(*rit++, 2);
  ASSERT_EQ(*rit++, 1);
  ASSERT_EQ(rit, s.rend());

  ft::set<int> const sc(arr, arr + 5);

  ft::set<int>::const_reverse_iterator ritc = sc.rbegin();
  ASSERT_EQ(*ritc++, 5);
  ASSERT_EQ(*ritc++, 4);
  ASSERT_EQ(*ritc++, 3);
  ASSERT_EQ(*ritc++, 2);
  ASSERT_EQ(*ritc++, 1);
  ASSERT_EQ(ritc, sc.rend());
}

TEST(TestSet, TestSetEmpty) {
  ft::set<int> s;
  ASSERT_TRUE(s.empty());
  s.insert(1);
  ASSERT_FALSE(s.empty());
}

TEST(TestSet, TestSetSize) {
  ft::set<int> s;
  ASSERT_EQ(s.size(), 0);
  s.insert(1);
  ASSERT_EQ(s.size(), 1);
  s.insert(2);
  ASSERT_EQ(s.size(), 2);
  s.insert(3);
  ASSERT_EQ(s.size(), 3);
  s.insert(4);
  ASSERT_EQ(s.size(), 4);
  s.insert(5);
  ASSERT_EQ(s.size(), 5);
}

TEST(TestSet, TestSetMaxSize) {
  ft::set<int> s;
  ASSERT_EQ(s.max_size(), std::numeric_limits<std::size_t>::max());
}

TEST(TestSet, TestSetInsert) {
  ft::set<int> s;

  ft::pair<ft::set<int>::iterator, bool> ret = s.insert(1);
  ASSERT_TRUE(ret.first == s.begin());
  ASSERT_TRUE(ret.second);

  ret = s.insert(1);
  ASSERT_TRUE(ret.first == s.begin());
  ASSERT_FALSE(ret.second);

  ret = s.insert(2);
  ft::set<int>::iterator it = s.begin();
  it++;
  ASSERT_TRUE(ret.first == it);
  ASSERT_TRUE(ret.second);

  ft::set<int>::iterator it2;
  it2 = s.insert(s.begin(), 3);
  ASSERT_EQ(*it2, 3);

  int arr[] = {4, 5, 6, 7, 8};
  s.insert(arr, arr + 5);
  ASSERT_EQ(s.size(), 8);
  ASSERT_EQ(s.count(4), 1);
}

TEST(TestSet, TestSetErase) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::iterator it = s.begin();
  it++;
  it++;
  it++;
  it++;
  s.erase(it);
  ASSERT_EQ(s.size(), 4);
  ASSERT_EQ(s.count(5), 0);

  ASSERT_EQ(s.erase(1), 1);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.count(1), 0);
  ASSERT_EQ(s.count(2), 1);

  ft::set<int>::iterator it3 = s.begin();
  it3++;
  it3++;
  s.erase(s.begin(), it3);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.count(3), 0);

  s.erase(s.begin(), s.end());
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s.count(1), 0);
}

TEST(TestSet, TestSetSwap) {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[] = {6, 7, 8, 9, 10};
  ft::set<int> s1(arr1, arr1 + 5);
  ft::set<int> s2(arr2, arr2 + 5);

  s1.swap(s2);
  ASSERT_EQ(s1.size(), 5);
  ASSERT_EQ(s2.size(), 5);
  ASSERT_EQ(s1.count(6), 1);
  ASSERT_EQ(s2.count(1), 1);
}

TEST(TestSet, TestSetClear) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);
  s.clear();
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s.count(1), 0);
}

TEST(TestSet, TestSetKeyCompare) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::key_compare cmp = s.key_comp();
  ASSERT_TRUE(cmp(1, 2));
  ASSERT_FALSE(cmp(2, 1));
  ASSERT_FALSE(cmp(1, 1));
}

TEST(TestSet, TestSetValueCompare) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::value_compare cmp = s.value_comp();
  ASSERT_TRUE(cmp(1, 2));
  ASSERT_FALSE(cmp(2, 1));
  ASSERT_FALSE(cmp(1, 1));
}

TEST(TestSet, TestSetFind) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::iterator it = s.find(1);
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, 1);

  it = s.find(6);
  ASSERT_TRUE(it == s.end());

  ft::set<int> const s2(arr, arr + 5);
  ft::set<int>::const_iterator cit = s2.find(1);
  ASSERT_TRUE(cit != s2.end());
  ASSERT_EQ(*cit, 1);
}

TEST(TestSet, TestSetCount) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(6), 0);
}

TEST(TestSet, TestSetLowerBound) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::iterator it = s.lower_bound(1);
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, 1);

  it = s.lower_bound(6);
  ASSERT_TRUE(it == s.end());

  ft::set<int> const s2(arr, arr + 5);
  ft::set<int>::const_iterator cit = s2.lower_bound(1);
  ASSERT_TRUE(cit != s2.end());
  ASSERT_EQ(*cit, 1);
}

TEST(TestSet, TestSetUpperBound) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::set<int>::iterator it = s.upper_bound(1);
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, 2);

  it = s.upper_bound(6);
  ASSERT_TRUE(it == s.end());

  ft::set<int> const s2(arr, arr + 5);
  ft::set<int>::const_iterator cit = s2.upper_bound(1);
  ASSERT_TRUE(cit != s2.end());
  ASSERT_EQ(*cit, 2);
}

TEST(TestSet, TestSetEqualRange) {
  int arr[] = {1, 2, 3, 4, 5};
  ft::set<int> s(arr, arr + 5);

  ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> p = s.equal_range(1);
  ASSERT_TRUE(p.first != s.end());
  ASSERT_EQ(*p.first, 1);
  ASSERT_TRUE(p.second != s.end());
  ASSERT_EQ(*p.second, 2);

  p = s.equal_range(6);
  ASSERT_TRUE(p.first == s.end());
  ASSERT_TRUE(p.second == s.end());

  ft::set<int> const s2(arr, arr + 5);
  ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> cp =
      s2.equal_range(1);
  ASSERT_TRUE(cp.first != s2.end());
  ASSERT_EQ(*cp.first, 1);
  ASSERT_TRUE(cp.second != s2.end());
  ASSERT_EQ(*cp.second, 2);
}

TEST(TestSet, TestSetGetAllocator) {
  ft::set<int> s;
  std::allocator<int> alloc;
  ASSERT_EQ(s.get_allocator(), alloc);
}

TEST(TestSet, TestSetComparisonOperators) {
  ft::set<int> s1;
  ft::set<int> s2;
  ft::set<int> s3;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(4);
  s1.insert(5);
  s2.insert(1);
  s2.insert(2);
  s2.insert(3);
  s2.insert(4);
  s2.insert(5);
  s3.insert(6);
  s3.insert(7);
  s3.insert(8);
  s3.insert(9);
  s3.insert(10);

  ASSERT_TRUE(s1 == s2);
  ASSERT_FALSE(s1 != s2);
  ASSERT_FALSE(s1 < s2);
  ASSERT_TRUE(s1 <= s2);
  ASSERT_FALSE(s1 > s2);
  ASSERT_TRUE(s1 >= s2);
  ASSERT_TRUE(s3 > s2);
  ASSERT_TRUE(s3 >= s2);
  ASSERT_TRUE(s2 < s3);
  ASSERT_TRUE(s2 <= s3);
}

TEST(TestSet, TestSetSwapOverload) {
  ft::set<int> s1;
  ft::set<int> s2;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s2.insert(4);
  s2.insert(5);
  s2.insert(6);
  ft::swap(s1, s2);
  ASSERT_EQ(s1.size(), 3);
  ASSERT_EQ(s2.size(), 3);
  ft::set<int>::iterator it = s1.begin();
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it, 6);
  it = s2.begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it, 3);
}
