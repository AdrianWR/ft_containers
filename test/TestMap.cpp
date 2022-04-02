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

TEST_F(TestMap, TestMapDefaultConstructor) {
  ft::map<int, int> mymap;
  ASSERT_EQ(mymap.size(), 0);
  ASSERT_TRUE(mymap.empty());
}

TEST_F(TestMap, TestMapRangeConstructor) {
  std::vector<ft::pair<char, int>> v;
  v.push_back(ft::pair<char, int>('a', 2));
  v.push_back(ft::pair<char, int>('b', 4));
  v.push_back(ft::pair<char, int>('c', 6));

  ft::map<char, int> mymap(v.begin(), v.end());
  ASSERT_EQ(mymap.size(), 3);
  ASSERT_EQ(mymap['a'], 2);
  ASSERT_EQ(mymap['b'], 4);
  ASSERT_EQ(mymap['c'], 6);
}

TEST_F(TestMap, TestMapCopyConstructor) {
  ft::map<char, int> mymap(MapChar);
  ASSERT_EQ(mymap.size(), 5);
  ASSERT_EQ(mymap['a'], 1);
  ASSERT_EQ(mymap['b'], 2);
  ASSERT_EQ(mymap['c'], 3);
  ASSERT_EQ(mymap['d'], 4);
  ASSERT_EQ(mymap['e'], 5);
}

TEST_F(TestMap, TestMapAssignmentOperator) {
  ft::map<char, int> mymap;
  mymap = MapChar;
  ASSERT_EQ(mymap['a'], 1);
  ASSERT_EQ(mymap['b'], 2);
  ASSERT_EQ(mymap['c'], 3);
  ASSERT_EQ(mymap['d'], 4);
  ASSERT_EQ(mymap['e'], 5);
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
  ASSERT_TRUE(mymap.empty());
}

TEST_F(TestMap, TestMapMaxSize) {
  ft::map<char, int> mymap;
  ASSERT_EQ(mymap.max_size(), std::numeric_limits<std::size_t>::max());
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

  mymap.insert(mymap.begin(), ft::pair<char, int>('f', 12));
  ASSERT_EQ(mymap.size(), 6);
  ASSERT_EQ(mymap['f'], 12);

  ft::pair<char, int> p[] = {ft::pair<char, int>('g', 14),
                             ft::pair<char, int>('h', 16),
                             ft::pair<char, int>('i', 18)};
  mymap.insert(p, p + 3);
  ASSERT_EQ(mymap.size(), 9);
  ASSERT_EQ(mymap['g'], 14);
  ASSERT_EQ(mymap['h'], 16);
  ASSERT_EQ(mymap['i'], 18);
}

TEST_F(TestMap, TestMapErase) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;

  mymap.erase('b');
  ASSERT_EQ(mymap.size(), 4);
  ASSERT_EQ(mymap['a'], 2);
  ASSERT_EQ(mymap['c'], 6);
  ASSERT_EQ(mymap['d'], 8);
  ASSERT_EQ(mymap['e'], 10);

  mymap.erase(mymap.begin());
  ASSERT_EQ(mymap.size(), 3);

  ft::map<char, int> m2;
  m2['a'] = 2;
  m2['b'] = 4;
  m2['c'] = 6;
  m2['d'] = 8;
  m2['e'] = 10;

  ft::map<char, int>::iterator it = m2.begin();
  ft::map<char, int>::iterator ite = m2.end();
  it++;
  ASSERT_EQ(it->first, 'b');
  // m2.erase(it, ite);
}

TEST_F(TestMap, TestClear) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;

  // mymap.clear();
  mymap.erase(mymap.begin(), mymap.end());
  ASSERT_EQ(mymap.size(), 0);
}

TEST_F(TestMap, TestMapSwap) {
  ft::map<char, int> mymap1;
  mymap1['a'] = 2;
  mymap1['b'] = 4;
  mymap1['c'] = 6;
  mymap1['d'] = 8;
  mymap1['e'] = 10;

  ft::map<char, int> mymap2;
  mymap2['f'] = 12;
  mymap2['g'] = 14;
  mymap2['h'] = 16;
  mymap2['i'] = 18;
  mymap2['j'] = 20;

  mymap1.swap(mymap2);
  ASSERT_EQ(mymap1.size(), 5);
  ASSERT_EQ(mymap1['f'], 12);
  ASSERT_EQ(mymap1['g'], 14);
  ASSERT_EQ(mymap1['h'], 16);
  ASSERT_EQ(mymap1['i'], 18);
  ASSERT_EQ(mymap1['j'], 20);

  ASSERT_EQ(mymap2.size(), 5);
  ASSERT_EQ(mymap2['a'], 2);
  ASSERT_EQ(mymap2['b'], 4);
  ASSERT_EQ(mymap2['c'], 6);
  ASSERT_EQ(mymap2['d'], 8);
  ASSERT_EQ(mymap2['e'], 10);
}

TEST_F(TestMap, TestFind) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;

  ft::map<char, int>::iterator it = mymap.find('a');
  ASSERT_EQ(it->first, 'a');
  ASSERT_EQ(it->second, 2);

  it = mymap.find('f');
  ASSERT_EQ(it, mymap.end());
}
