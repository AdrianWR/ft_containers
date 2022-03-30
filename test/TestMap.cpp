#include <gtest/gtest.h>

#include "map.hpp"

class TestMap : public ::testing::Test {
protected:
  virtual void SetUp() { EmptyMap = new ft::map<int, int>; }

  virtual void TearDown() { delete EmptyMap; }

  ft::map<int, int> *EmptyMap;
};

TEST_F(TestMap, TestSize) { ASSERT_EQ(EmptyMap->size(), 0); }
