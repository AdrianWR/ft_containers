#include "iterator.hpp"
#include <gtest/gtest.h>
#include <iterator>
#include <list>
#include <vector>

TEST(TestReverseIterator, TestReverseIterator) {
  std::vector<int> v{1, 2, 3, 4, 5};
  std::list<int> l{1, 2, 3, 4, 5};
}
