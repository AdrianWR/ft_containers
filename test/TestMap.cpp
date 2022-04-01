#include <gtest/gtest.h>

#include "map.hpp"

class TestMap : public ::testing::Test {
protected:
  virtual void SetUp() {
    MapChar['a'] = 1;
    MapChar['b'] = 2;
    MapChar['c'] = 3;
    MapChar['d'] = 4;
    MapChar['e'] = 5;
  }

  virtual void TearDown() {}

  ft::map<int, int> EmptyMap;
  ft::map<char, int> MapChar;
};

TEST_F(TestMap, TestMapDefaultConstructor) { ASSERT_EQ(EmptyMap.size(), 0); }

// TEST(TestMapConstructor, TestMapIteratorConstructor) {
//   std::vector<std::pair<int, int>> v = {{1, 2}, {3, 4}, {5, 6}};
//   ft::map<int, int> m(v.begin(), v.end());
//   ASSERT_EQ(m.size(), 3);
// }

TEST_F(TestMap, TestMapIteratorConstructor) {
  std::vector<ft::pair<char, int>> v;
  v.push_back(ft::pair<char, int>('a', 2));
  v.push_back(ft::pair<char, int>('b', 4));
  v.push_back(ft::pair<char, int>('c', 6));

  ft::map<char, int> mymap(v.begin(), v.end());
  ASSERT_EQ(mymap.size(), 3);
  ASSERT_EQ(mymap.begin()->first, 'a');
  ASSERT_EQ(mymap.begin()->second, 2);
}

TEST_F(TestMap, TestMapCopyConstructor) {
  ft::map<char, int> mymap(MapChar);
  ASSERT_EQ(mymap.size(), 5);
  ASSERT_EQ(mymap.begin()->first, 'a');
  ASSERT_EQ(mymap.begin()->second, 1);
}

TEST_F(TestMap, TestMapAssignmentOperator) {
  ft::map<char, int> mymap;
  mymap = MapChar;
  ASSERT_EQ(mymap.size(), 5);
  ASSERT_EQ(mymap.begin()->first, 'a');
  ASSERT_EQ(mymap.begin()->second, 1);
}

TEST_F(TestMap, TestMapBegin) {
  ft::map<char, int> mymap(MapChar);
  ASSERT_EQ(mymap.begin()->first, 'a');
  ASSERT_EQ(mymap.begin()->second, 1);

  ft::map<char, int>::iterator it = mymap.begin();
  char c = 'a';
  for (; it != mymap.end(); ++it) {
    ASSERT_EQ(it->first, c);
    ASSERT_EQ(it->second, MapChar[c]);
    c++;
  }
}

TEST_F(TestMap, TestMapEnd) {
  ft::map<char, int> mymap(MapChar);

  ft::map<char, int>::iterator it = mymap.end();
  it--;
  ASSERT_EQ(it->first, 'e');
  ASSERT_EQ(it->second, 5);
  char c = 'e';
  for (; it != mymap.begin(); --it) {
    ASSERT_EQ(it->first, c);
    ASSERT_EQ(it->second, MapChar[c]);
    c--;
  }
}

TEST_F(TestMap, TestMapRBegin) {
  ft::map<char, int> mymap(MapChar);
  ASSERT_EQ(mymap.rbegin()->first, 'e');
  ASSERT_EQ(mymap.rbegin()->second, 5);

  ft::map<char, int>::reverse_iterator it = mymap.rbegin();
  char c = 'e';
  for (; it != mymap.rend(); ++it) {
    ASSERT_EQ(it->first, c);
    ASSERT_EQ(it->second, MapChar[c]);
    c--;
  }
}

TEST_F(TestMap, TestMapREnd) {
  ft::map<char, int> mymap(MapChar);
  ft::map<char, int>::reverse_iterator it = mymap.rend();
  it--;
  ASSERT_EQ(it->first, 'a');
  ASSERT_EQ(it->second, 1);
  char c = 'a';
  for (; it != mymap.rbegin(); --it) {
    ASSERT_EQ(it->first, c);
    ASSERT_EQ(it->second, MapChar[c]);
    c++;
  }
}

TEST_F(TestMap, TestMapSize) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  ASSERT_EQ(mymap.size(), 3);

  mymap['d'] = 8;
  ASSERT_EQ(mymap.size(), 4);

  mymap.erase('d');
  ASSERT_EQ(mymap.size(), 3);
}

TEST_F(TestMap, TestMapEmpty) {
  ft::map<char, int> mymap;
  ASSERT_TRUE(mymap.empty());

  mymap['a'] = 2;
  ASSERT_FALSE(mymap.empty());

  mymap.erase('a');

  // mymap.erase('a');
  // ASSERT_TRUE(mymap.empty());
}

TEST_F(TestMap, TestMapElementAccess) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;

  ASSERT_EQ(mymap['a'], 2);
  ASSERT_EQ(mymap['b'], 4);
  ASSERT_EQ(mymap['c'], 6);
}

TEST_F(TestMap, TestMapClear) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;

  mymap.clear();
  ASSERT_EQ(mymap.size(), 0);
}

TEST_F(TestMap, TestMapInsert) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;

  mymap.insert(ft::pair<char, int>('d', 8));
  ASSERT_EQ(mymap.size(), 4);
  ASSERT_EQ(mymap['d'], 8);

  mymap.insert(ft::pair<char, int>('e', 10));
  ASSERT_EQ(mymap.size(), 5);
  ASSERT_EQ(mymap['e'], 10);
}
