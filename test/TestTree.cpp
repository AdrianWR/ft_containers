#include <gtest/gtest.h>
#include <memory>

#include "nullptr.hpp"
#include "tree.hpp"

#include <iostream>

class TestNodeIterator : public ::testing::Test {

public:
  ft::Node<int> *n13;
  ft::Node<int> *n8;
  ft::Node<int> *n1;
  ft::Node<int> *n6;
  ft::Node<int> *n11;
  ft::Node<int> *n17;
  ft::Node<int> *n15;
  ft::Node<int> *n25;
  ft::Node<int> *n22;
  ft::Node<int> *n27;

  TestNodeIterator() {}

  void SetUp() {
    n13 = new ft::Node<int>(13, ft::color::BLACK);
    n8 = new ft::Node<int>(8, ft::color::RED);
    n1 = new ft::Node<int>(1, ft::color::BLACK);
    n6 = new ft::Node<int>(6, ft::color::RED);
    n11 = new ft::Node<int>(11, ft::color::BLACK);
    n17 = new ft::Node<int>(17, ft::color::RED);
    n15 = new ft::Node<int>(15, ft::color::BLACK);
    n25 = new ft::Node<int>(25, ft::color::BLACK);
    n22 = new ft::Node<int>(22, ft::color::RED);
    n27 = new ft::Node<int>(27, ft::color::RED);
    n13->parent(ft::_nullptr);
    n13->left(n8);
    n13->right(n17);
    n8->parent(n13);
    n8->left(n1);
    n8->right(n11);
    n1->parent(n8);
    n1->left(ft::_nullptr);
    n1->right(n6);
    n6->parent(n1);
    n6->left(ft::_nullptr);
    n6->right(ft::_nullptr);
    n11->parent(n8);
    n11->left(ft::_nullptr);
    n11->right(ft::_nullptr);
    n17->parent(n13);
    n17->left(n15);
    n17->right(n25);
    n15->parent(n17);
    n15->left(ft::_nullptr);
    n15->right(ft::_nullptr);
    n25->parent(n17);
    n25->left(n22);
    n25->right(n27);
    n22->parent(n25);
    n22->left(ft::_nullptr);
    n22->right(ft::_nullptr);
    n27->parent(n25);
    n27->left(ft::_nullptr);
    n27->right(ft::_nullptr);
  }

  void TearDown() {
    delete n6;
    delete n1;
    delete n8;
    delete n11;
    delete n22;
    delete n27;
    delete n25;
    delete n15;
    delete n17;
    delete n13;
  }
};

TEST(TestNode, TestNodeConstructor) {
  ft::Node<int> node_zero;
  EXPECT_EQ(node_zero.parent(), ft::_nullptr);
  EXPECT_EQ(node_zero.left(), ft::_nullptr);
  EXPECT_EQ(node_zero.right(), ft::_nullptr);

  ft::Node<int> node(1);
  EXPECT_EQ(node.value(), 1);
  EXPECT_EQ(node.left(), ft::_nullptr);
  EXPECT_EQ(node.right(), ft::_nullptr);
  EXPECT_EQ(node.parent(), ft::_nullptr);

  ft::Node<int> node2(2, ft::color::RED, &node);
  EXPECT_EQ(node2.value(), 2);
  EXPECT_EQ(node2.parent(), &node);
  EXPECT_EQ(node2.left(), ft::_nullptr);
  EXPECT_EQ(node2.right(), ft::_nullptr);
  EXPECT_EQ(node2.color(), ft::color::RED);

  ft::Node<int> node3(node2);
  EXPECT_EQ(node3.value(), 2);
  EXPECT_EQ(node3.parent(), &node);
  EXPECT_EQ(node3.left(), ft::_nullptr);
  EXPECT_EQ(node3.right(), ft::_nullptr);
  EXPECT_EQ(node3.color(), ft::color::RED);

  ft::Node<int> node4(node);
  EXPECT_EQ(node4.value(), 1);
  EXPECT_EQ(node4.parent(), ft::_nullptr);
  EXPECT_EQ(node4.left(), ft::_nullptr);
  EXPECT_EQ(node4.right(), ft::_nullptr);
  EXPECT_EQ(node4.color(), ft::color::RED);

  ft::Node<int> node5;
  node5 = node;
  EXPECT_EQ(node5.value(), 1);
  EXPECT_EQ(node5.parent(), ft::_nullptr);
  EXPECT_EQ(node5.left(), ft::_nullptr);
  EXPECT_EQ(node5.right(), ft::_nullptr);
  EXPECT_EQ(node5.color(), ft::color::RED);

  node5 = node2;
  EXPECT_EQ(node5.value(), 2);
  EXPECT_EQ(node5.parent(), &node);
  EXPECT_EQ(node5.left(), ft::_nullptr);
  EXPECT_EQ(node5.right(), ft::_nullptr);
  EXPECT_EQ(node5.color(), ft::color::RED);
}

TEST_F(TestNodeIterator, TestNodeIterator) {
  ft::Node<int> *root = n13;
  EXPECT_EQ(root->minimum(), n1);
  EXPECT_EQ(root->maximum(), n27);
  EXPECT_EQ(root->previous(), n11);
  EXPECT_EQ(root->next(), n15);

  EXPECT_EQ(n1->next(), n6);
  EXPECT_EQ(n6->next(), n8);
  EXPECT_EQ(n8->next(), n11);
  EXPECT_EQ(n11->next(), n13);
  EXPECT_EQ(n13->next(), n15);
  EXPECT_EQ(n15->next(), n17);
  EXPECT_EQ(n17->next(), n22);
  EXPECT_EQ(n22->next(), n25);
  EXPECT_EQ(n25->next(), n27);

  EXPECT_EQ(n27->previous(), n25);
  EXPECT_EQ(n25->previous(), n22);
  EXPECT_EQ(n22->previous(), n17);
  EXPECT_EQ(n17->previous(), n15);
  EXPECT_EQ(n15->previous(), n13);
  EXPECT_EQ(n13->previous(), n11);
  EXPECT_EQ(n11->previous(), n8);
  EXPECT_EQ(n8->previous(), n6);
  EXPECT_EQ(n6->previous(), n1);
}

// TEST(TestTree, TestTreeDefaultConstructor) {
//   ft::RedBlackTree<int> tree;
//   EXPECT_EQ(tree.get_root()->parent, ft::_nullptr);
//   EXPECT_EQ(tree.get_root()->left, ft::_nullptr);
//   EXPECT_EQ(tree.get_root()->right, ft::_nullptr);
// }
//
// TEST(TestTree, TestTreeValueConstructor) {
//   ft::RedBlackTree<int> tree(42);
//   EXPECT_EQ(tree.get_root()->value(), 42);
//   EXPECT_EQ(tree.get_root()->parent, ft::_nullptr);
//   EXPECT_EQ(tree.get_root()->left, ft::_nullptr);
//   EXPECT_EQ(tree.get_root()->right, ft::_nullptr);
//   EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
// }

// TEST(TestTree, TestTreeCopyConstructor) {
//   ft::RedBlackTree<int> tree(42);
//   ft::RedBlackTree<int> tree_copy(tree);
//   EXPECT_EQ(tree_copy.get_root()->value(), 42);
//   EXPECT_EQ(tree_copy.get_root()->parent, ft::_nullptr);
//   EXPECT_EQ(tree_copy.get_root()->left, ft::_nullptr);
//   EXPECT_EQ(tree_copy.get_root()->right, ft::_nullptr);
//   EXPECT_EQ(tree_copy.get_root()->color, ft::color::BLACK);
// }
