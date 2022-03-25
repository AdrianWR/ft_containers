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
    n13->set_parent(ft::_nullptr);
    n13->set_left(n8);
    n13->set_right(n17);
    n8->set_parent(n13);
    n8->set_left(n1);
    n8->set_right(n11);
    n1->set_parent(n8);
    n1->set_left(ft::_nullptr);
    n1->set_right(n6);
    n6->set_parent(n1);
    n6->set_left(ft::_nullptr);
    n6->set_right(ft::_nullptr);
    n11->set_parent(n8);
    n11->set_left(ft::_nullptr);
    n11->set_right(ft::_nullptr);
    n17->set_parent(n13);
    n17->set_left(n15);
    n17->set_right(n25);
    n15->set_parent(n17);
    n15->set_left(ft::_nullptr);
    n15->set_right(ft::_nullptr);
    n25->set_parent(n17);
    n25->set_left(n22);
    n25->set_right(n27);
    n22->set_parent(n25);
    n22->set_left(ft::_nullptr);
    n22->set_right(ft::_nullptr);
    n27->set_parent(n25);
    n27->set_left(ft::_nullptr);
    n27->set_right(ft::_nullptr);
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

TEST_F(TestNodeIterator, TestNodeIteratorConstructor) {
  ft::NodeIterator<int> it;

  ft::NodeIterator<int> it2(n13);
  EXPECT_EQ(*it2, 13);

  it = it2;
  EXPECT_EQ(*it, 13);
}

TEST_F(TestNodeIterator, TestNodeIteratorComparisonOperator) {
  ft::NodeIterator<int> it1(n13);
  ft::NodeIterator<int> it2(n13);
  ft::NodeIterator<int> it3(n8);

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_FALSE(it1 != it2);
  EXPECT_TRUE(it1 != it3);
}

TEST_F(TestNodeIterator, TestNodeIteratorIncrement) {
  ft::NodeIterator<int> it(n1);

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 6);
  ++it;
  EXPECT_EQ(*it, 8);
  ++it;
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 13);
  EXPECT_EQ(*it++, 13);
  EXPECT_EQ(*it++, 15);
  EXPECT_EQ(*it++, 17);
  EXPECT_EQ(*it++, 22);
  EXPECT_EQ(*it++, 25);
  EXPECT_EQ(*it, 27);
}

TEST_F(TestNodeIterator, TestNodeIteratorDecrement) {
  ft::NodeIterator<int> it2(n27);

  EXPECT_EQ(*it2, 27);
  --it2;
  EXPECT_EQ(*it2, 25);
  --it2;
  EXPECT_EQ(*it2, 22);
  it2--;
  EXPECT_EQ(*it2, 17);
  it2--;
  EXPECT_EQ(*it2--, 15);
  EXPECT_EQ(*it2--, 13);
  EXPECT_EQ(*it2--, 11);
  EXPECT_EQ(*it2--, 8);
  EXPECT_EQ(*it2--, 6);
  EXPECT_EQ(*it2, 1);
}

TEST(TestTreeConstructor, TestTreeDefaultConstructor) {
  ft::RedBlackTree<int> tree;
  EXPECT_EQ(tree.get_root()->color(), ft::color::BLACK);
}

TEST(TestTreeConstructor, TestTreeValueConstructor) {
  ft::RedBlackTree<int> tree(42);
  EXPECT_EQ(tree.get_root()->value(), 42);
  EXPECT_EQ(tree.get_root()->parent(), tree.get_nil());
  EXPECT_EQ(tree.get_root()->left(), tree.get_nil());
  EXPECT_EQ(tree.get_root()->right(), tree.get_nil());
  EXPECT_EQ(tree.get_root()->color(), ft::color::BLACK);
}

// TEST(TestTree, TestTreeCopyConstructor) {
//   ft::RedBlackTree<int> tree(42);
//   ft::RedBlackTree<int> tree_copy(tree);
//   EXPECT_EQ(tree_copy.get_root()->value(), 42);
//   EXPECT_EQ(tree_copy.get_root()->parent(), tree.get_root()->parent());
//   EXPECT_EQ(tree_copy.get_root()->left(), tree.get_root()->left());
//   EXPECT_EQ(tree_copy.get_root()->right(), tree.get_root()->right());
//   EXPECT_EQ(tree_copy.get_root()->color(), tree.get_root()->color());
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
  EXPECT_EQ(tree.get_root()->color(), ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->parent(), tree.get_nil());
  EXPECT_EQ(tree.get_root()->left()->value(), 8);
  EXPECT_EQ(tree.get_root()->left()->color(), ft::color::RED);
  EXPECT_EQ(tree.get_root()->left()->left()->value(), 1);
  EXPECT_EQ(tree.get_root()->left()->left()->color(), ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->left()->left()->right()->value(), 6);
  EXPECT_EQ(tree.get_root()->left()->left()->right()->color(), ft::color::RED);
  EXPECT_EQ(tree.get_root()->left()->right()->value(), 11);
  EXPECT_EQ(tree.get_root()->left()->right()->color(), ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right()->value(), 17);
  EXPECT_EQ(tree.get_root()->right()->color(), ft::color::RED);
  EXPECT_EQ(tree.get_root()->right()->left()->value(), 15);
  EXPECT_EQ(tree.get_root()->right()->left()->color(), ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right()->right()->value(), 25);
  EXPECT_EQ(tree.get_root()->right()->right()->color(), ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right()->right()->left()->value(), 22);
  EXPECT_EQ(tree.get_root()->right()->right()->left()->color(), ft::color::RED);
  EXPECT_EQ(tree.get_root()->right()->right()->right()->value(), 27);
  EXPECT_EQ(tree.get_root()->right()->right()->right()->color(),
            ft::color::RED);
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
}
