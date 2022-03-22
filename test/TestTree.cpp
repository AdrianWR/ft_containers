#include <gtest/gtest.h>

#include "nullptr.hpp"
#include "tree.hpp"

TEST(TestTree, TestTree) { EXPECT_EQ(1, 1); }

TEST(TestNode, TestNode) {
  ft::Node<int> node(1);
  EXPECT_EQ(node.get_value(), 1);
  EXPECT_EQ(node.get_left(), ft::_nullptr);
  EXPECT_EQ(node.get_right(), ft::_nullptr);
}
