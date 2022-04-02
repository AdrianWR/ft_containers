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

TEST_F(TestMap, TestKeyComp) {
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

  ft::map<char, int>::key_compare kc = mymap1.key_comp();
  ASSERT_TRUE(kc('a', 'b'));
  ASSERT_TRUE(kc('b', 'c'));
  ASSERT_TRUE(kc('c', 'd'));
  ASSERT_TRUE(kc('d', 'e'));
  ASSERT_TRUE(kc('e', 'f'));
  ASSERT_TRUE(kc('f', 'g'));
  ASSERT_TRUE(kc('g', 'h'));
  ASSERT_TRUE(kc('h', 'i'));
  ASSERT_TRUE(kc('i', 'j'));

  ft::map<char, int>::iterator it;
  for (it = mymap1.begin(); it != mymap1.end(); ++it) {
    ASSERT_TRUE(kc(it->first, it->first + 1));
  }
}

TEST_F(TestMap, TestMapValueComp) {
  ft::map<char, int> mymap1;
  mymap1['a'] = 2;
  mymap1['b'] = 4;
  mymap1['c'] = 6;
  mymap1['d'] = 8;
  mymap1['e'] = 10;

  ft::map<char, int>::value_compare vc = mymap1.value_comp();

  ft::map<char, int>::iterator it;
  ft::pair<char, int> highest = ft::make_pair('f', 12);
  for (it = mymap1.begin(); it != mymap1.end(); ++it) {
    ASSERT_TRUE(vc(*it, highest));
  }
}

TEST_F(TestMap, TestMapFind) {
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

  const ft::map<char, int> mymap2(mymap);
  ft::map<char, int>::const_iterator it2 = mymap2.find('a');
  ASSERT_EQ(it2->first, 'a');
  ASSERT_EQ(it2->second, 2);
};

TEST_F(TestMap, TestMapCount) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;

  ASSERT_EQ(mymap.count('a'), 1);
  ASSERT_EQ(mymap.count('f'), 0);
};

TEST_F(TestMap, TestMapLowerBound) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;
  mymap['f'] = 12;
  mymap['i'] = 18;
  mymap['l'] = 24;
  mymap['m'] = 26;
  mymap['p'] = 32;

  ft::map<char, int>::iterator it = mymap.lower_bound('a');
  ASSERT_EQ(it->first, 'a');
  ASSERT_EQ(it->second, 2);

  it = mymap.lower_bound('b');
  ASSERT_EQ(it->first, 'b');
  ASSERT_EQ(it->second, 4);

  it = mymap.lower_bound('g');
  ASSERT_EQ(it->first, 'i');

  const ft::map<char, int> mymap2(mymap);
  ft::map<char, int>::const_iterator it2 = mymap2.lower_bound('a');
  ASSERT_EQ(it2->first, 'a');
  ASSERT_EQ(it2->second, 2);

  ft::map<char, int>::const_iterator it3 = mymap2.lower_bound('q');
  ASSERT_EQ(it3, mymap2.end());
};

TEST_F(TestMap, TestMapUpperBound) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;
  mymap['f'] = 12;
  mymap['i'] = 18;
  mymap['l'] = 24;
  mymap['m'] = 26;
  mymap['p'] = 32;

  ft::map<char, int>::iterator it = mymap.upper_bound('a');
  ASSERT_EQ(it->first, 'b');
  ASSERT_EQ(it->second, 4);

  it = mymap.upper_bound('b');
  ASSERT_EQ(it->first, 'c');
  ASSERT_EQ(it->second, 6);

  it = mymap.upper_bound('g');
  ASSERT_EQ(it->first, 'i');

  const ft::map<char, int> mymap2(mymap);
  ft::map<char, int>::const_iterator it2 = mymap2.upper_bound('a');
  ASSERT_EQ(it2->first, 'b');
  ASSERT_EQ(it2->second, 4);

  ft::map<char, int>::const_iterator it3 = mymap2.upper_bound('q');
  ASSERT_EQ(it3, mymap2.end());
};

TEST_F(TestMap, TestMapEqualRange) {
  ft::map<char, int> mymap;
  mymap['a'] = 2;
  mymap['b'] = 4;
  mymap['c'] = 6;
  mymap['d'] = 8;
  mymap['e'] = 10;
  mymap['f'] = 12;
  mymap['i'] = 18;
  mymap['l'] = 24;
  mymap['m'] = 26;
  mymap['p'] = 32;

  ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> it =
      mymap.equal_range('a');

  ASSERT_EQ(it.first->first, 'a');
  ASSERT_EQ(it.second->first, 'b');

  it = mymap.equal_range('b');
  ASSERT_EQ(it.first->first, 'b');
  ASSERT_EQ(it.second->first, 'c');

  it = mymap.equal_range('g');
  ASSERT_EQ(it.first->first, 'i');
  ASSERT_EQ(it.second->first, 'i');

  const ft::map<char, int> mymap2(mymap);

  ft::pair<ft::map<char, int>::const_iterator,
           ft::map<char, int>::const_iterator>
      it2 = mymap2.equal_range('a');

  ASSERT_EQ(it2.first->first, 'a');
  ASSERT_EQ(it2.second->first, 'b');

  it2 = mymap2.equal_range('b');
  ASSERT_EQ(it2.first->first, 'b');
  ASSERT_EQ(it2.second->first, 'c');

  it2 = mymap2.equal_range('g');
  ASSERT_EQ(it2.first->first, 'i');
  ASSERT_EQ(it2.second->first, 'i');
};

TEST_F(TestMap, TestGetAllocator) {
  ft::map<char, int> mymap;
  std::allocator<std::pair<const char, int>> alloc;
  ASSERT_EQ(mymap.get_allocator(), alloc);
};

TEST_F(TestMap, TestMapComparisonOperators) {
  ft::map<char, int> mymap1;
  ft::map<char, int> mymap2;
  ft::map<char, int> mymap3;
  ft::map<char, int> mymap4;

  mymap1['a'] = 2;
  mymap1['b'] = 4;
  mymap1['c'] = 6;
  mymap1['d'] = 8;
  mymap1['e'] = 10;
  mymap1['f'] = 12;
  mymap1['i'] = 18;
  mymap1['l'] = 24;
  mymap1['m'] = 26;
  mymap1['p'] = 32;

  mymap2['a'] = 2;
  mymap2['b'] = 4;
  mymap2['c'] = 6;
  mymap2['d'] = 8;
  mymap2['e'] = 10;
  mymap2['f'] = 12;
  mymap2['i'] = 18;

  mymap3['a'] = 2;
  mymap3['b'] = 4;
  mymap3['c'] = 6;
  mymap3['d'] = 8;
  mymap3['e'] = 10;
  mymap3['f'] = 12;
  mymap3['i'] = 18;
  mymap3['l'] = 24;
  mymap3['m'] = 26;
  mymap3['p'] = 32;

  ASSERT_TRUE(mymap1 == mymap3);
  ASSERT_TRUE(mymap1 != mymap2);
  ASSERT_TRUE(mymap2 < mymap1);
  ASSERT_TRUE(mymap1 > mymap2);
  ASSERT_TRUE(mymap1 <= mymap3);
  ASSERT_TRUE(mymap1 >= mymap3);
  ASSERT_TRUE(mymap1 <= mymap1);
  ASSERT_TRUE(mymap1 >= mymap1);
};

TEST_F(TestMap, TestMapSwapOperator) {
  ft::map<char, int> mymap1;
  ft::map<char, int> mymap2;

  mymap1['a'] = 2;
  mymap1['b'] = 4;
  mymap1['c'] = 6;
  mymap1['d'] = 8;
  mymap1['e'] = 10;
  mymap1['f'] = 12;
  mymap1['i'] = 18;
  mymap1['l'] = 24;
  mymap1['m'] = 26;
  mymap1['p'] = 32;

  mymap2['a'] = 2;
  mymap2['b'] = 4;
  mymap2['c'] = 6;
  mymap2['d'] = 8;
  mymap2['e'] = 10;
  mymap2['f'] = 12;
  mymap2['i'] = 18;
  mymap2['l'] = 24;
  mymap2['m'] = 26;
  mymap2['p'] = 32;

  ft::swap(mymap1, mymap2);

  ASSERT_TRUE(mymap1 == mymap2);
  ASSERT_TRUE(mymap2 == mymap1);
}
