#include <gtest/gtest.h>
#include <memory>

#include "nullptr.hpp"
#include "tree.hpp"

#include <iostream>

TEST(TestNode, TestNodeConstructor) {
  ft::Node<int> node_zero;
  EXPECT_EQ(node_zero.parent, ft::_nullptr);
  EXPECT_EQ(node_zero.left, ft::_nullptr);
  EXPECT_EQ(node_zero.right, ft::_nullptr);

  ft::Node<int> node(1);
  EXPECT_EQ(node.value(), 1);
  EXPECT_EQ(node.left, ft::_nullptr);
  EXPECT_EQ(node.right, ft::_nullptr);
  EXPECT_EQ(node.parent, ft::_nullptr);

  ft::Node<int> node2(2, ft::color::RED, &node);
  EXPECT_EQ(node2.value(), 2);
  EXPECT_EQ(node2.parent, &node);
  EXPECT_EQ(node2.left, ft::_nullptr);
  EXPECT_EQ(node2.right, ft::_nullptr);
  EXPECT_EQ(node2.color, ft::color::RED);

  ft::Node<int> node3(node2);
  EXPECT_EQ(node3.value(), 2);
  EXPECT_EQ(node3.parent, &node);
  EXPECT_EQ(node3.left, ft::_nullptr);
  EXPECT_EQ(node3.right, ft::_nullptr);
  EXPECT_EQ(node3.color, ft::color::RED);

  ft::Node<int> node4(node);
  EXPECT_EQ(node4.value(), 1);
  EXPECT_EQ(node4.parent, ft::_nullptr);
  EXPECT_EQ(node4.left, ft::_nullptr);
  EXPECT_EQ(node4.right, ft::_nullptr);
  EXPECT_EQ(node4.color, ft::color::RED);

  ft::Node<int> node5;
  node5 = node;
  EXPECT_EQ(node5.value(), 1);
  EXPECT_EQ(node5.parent, ft::_nullptr);
  EXPECT_EQ(node5.left, ft::_nullptr);
  EXPECT_EQ(node5.right, ft::_nullptr);
  EXPECT_EQ(node5.color, ft::color::RED);

  node5 = node2;
  EXPECT_EQ(node5.value(), 2);
  EXPECT_EQ(node5.parent, &node);
  EXPECT_EQ(node5.left, ft::_nullptr);
  EXPECT_EQ(node5.right, ft::_nullptr);
  EXPECT_EQ(node5.color, ft::color::RED);
}

TEST(TestTreeConstructor, TestTreeDefaultConstructor) {
  ft::RedBlackTree<int> tree;
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
}

TEST(TestTreeConstructor, TestTreeValueConstructor) {
  ft::RedBlackTree<int> tree(42);
  EXPECT_EQ(tree.get_root()->value(), 42);
  EXPECT_EQ(tree.get_root()->parent, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left, tree.get_nil());
  EXPECT_EQ(tree.get_root()->right, tree.get_nil());
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
}

// TEST(TestTree, TestTreeCopyConstructor) {
//   ft::RedBlackTree<int> tree(42);
//   ft::RedBlackTree<int> tree_copy(tree);
//   EXPECT_EQ(tree_copy.get_root()->value(), 42);
//   EXPECT_EQ(tree_copy.get_root()->parent(), tree.get_root()->parent());
//   EXPECT_EQ(tree_copy.get_root()->left, tree.get_root()->left);
//   EXPECT_EQ(tree_copy.get_root()->right, tree.get_root()->right);
//   EXPECT_EQ(tree_copy.get_root()->color, tree.get_root()->color);
// }

class TestTree : public ::testing::Test {
public:
  ft::RedBlackTree<int> tree;

  void SetUp() override {
    tree.insert(13);
    tree.insert(17);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(22);
    tree.insert(1);
    tree.insert(25);
    tree.insert(6);
    tree.insert(27);
  }
};

TEST_F(TestTree, TestTreeInsert) {
  EXPECT_EQ(tree.get_root()->value(), 13);
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->parent, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->value(), 8);
  EXPECT_EQ(tree.get_root()->left->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->left->left->value(), 1);
  EXPECT_EQ(tree.get_root()->left->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->left->left->right->value(), 6);
  EXPECT_EQ(tree.get_root()->left->left->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->left->right->value(), 11);
  EXPECT_EQ(tree.get_root()->left->right->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->value(), 17);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->value(), 15);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->value(), 25);
  EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->left->value(), 22);
  EXPECT_EQ(tree.get_root()->right->right->left->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->right->right->value(), 27);
  EXPECT_EQ(tree.get_root()->right->right->right->color, ft::color::RED);
}

TEST_F(TestTree, TestFind) {
  ft::RedBlackTree<int>::iterator it = tree.find(13);

  EXPECT_EQ(*it, 13);
  it = tree.find(17);
  EXPECT_EQ(*it, 17);

  it = tree.find(-1);
  EXPECT_EQ(it, tree.end());
}

TEST_F(TestTree, TestRemove) {
  tree.remove(13);
  EXPECT_EQ(tree.get_root()->value(), 15);
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->value(), 25);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->value(), 17);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);

  tree.remove(11);
  EXPECT_EQ(tree.get_root()->left->value(), 6);
  EXPECT_EQ(tree.get_root()->left->left->value(), 1);
  EXPECT_EQ(tree.get_root()->left->left->left, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->left->right, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->right->value(), 8);
  EXPECT_EQ(tree.get_root()->left->right->left, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->right->right, tree.get_nil());

  tree.remove(17);
  EXPECT_EQ(tree.get_root()->right->value(), 25);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->value(), 22);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->value(), 27);
  EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
}
