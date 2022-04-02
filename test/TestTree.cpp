#include <gtest/gtest.h>
#include <map>
#include <memory>

#include "nullptr.hpp"
#include "tree.hpp"

#include <iostream>

class TestTree : public ::testing::Test {
public:
  ft::RedBlackTree<int, int> tree;

  void SetUp() {
    tree.insert_unique(ft::make_pair<int, int>(13, 13));
    tree.insert_unique(ft::make_pair<int, int>(17, 17));
    tree.insert_unique(ft::make_pair<int, int>(8, 8));
    tree.insert_unique(ft::make_pair<int, int>(11, 11));
    tree.insert_unique(ft::make_pair<int, int>(15, 15));
    tree.insert_unique(ft::make_pair<int, int>(22, 22));
    tree.insert_unique(ft::make_pair<int, int>(1, 1));
    tree.insert_unique(ft::make_pair<int, int>(25, 25));
    tree.insert_unique(ft::make_pair<int, int>(6, 6));
    tree.insert_unique(ft::make_pair<int, int>(27, 27));
  }
};

TEST(TestNode, TestNodeConstructor) {
  ft::Node<int> node_zero;
  EXPECT_EQ(node_zero.parent, ft::_nullptr);
  EXPECT_EQ(node_zero.left, ft::_nullptr);
  EXPECT_EQ(node_zero.right, ft::_nullptr);

  ft::Node<int> node(1, ft::color::RED, ft::_nullptr);
  EXPECT_EQ(node.left, ft::_nullptr);
  EXPECT_EQ(node.right, ft::_nullptr);
  EXPECT_EQ(node.parent, ft::_nullptr);

  ft::Node<int> node3(node);
  EXPECT_EQ(node3.parent, ft::_nullptr);
  EXPECT_EQ(node3.left, ft::_nullptr);
  EXPECT_EQ(node3.right, ft::_nullptr);
  EXPECT_EQ(node3.color, ft::color::RED);

  ft::Node<int> node5;
  node5 = node;
  EXPECT_EQ(node5.parent, ft::_nullptr);
  EXPECT_EQ(node5.left, ft::_nullptr);
  EXPECT_EQ(node5.right, ft::_nullptr);
  EXPECT_EQ(node5.color, ft::color::RED);
}

TEST(TestTreeConstructor, TestTreeDefaultConstructor) {
  ft::RedBlackTree<int, int> tree;
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
}

TEST_F(TestTree, TestTreeCopyConstructor) {
  ft::RedBlackTree<int, int> tree_copy(tree);
  EXPECT_TRUE(tree_copy == tree);
}

TEST_F(TestTree, TestTreeInsert) {
  EXPECT_EQ(tree.get_root()->data->first, 13);
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->parent, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->data->first, 8);
  EXPECT_EQ(tree.get_root()->left->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->left->left->data->first, 1);
  EXPECT_EQ(tree.get_root()->left->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->left->left->right->data->first, 6);
  EXPECT_EQ(tree.get_root()->left->left->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->left->right->data->first, 11);
  EXPECT_EQ(tree.get_root()->left->right->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->data->first, 17);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->data->first, 15);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->data->first, 25);
  EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->left->data->first, 22);
  EXPECT_EQ(tree.get_root()->right->right->left->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->right->right->data->first, 27);
  EXPECT_EQ(tree.get_root()->right->right->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->right->right->right, tree.get_nil());
  EXPECT_EQ(tree.get_root()->right->right->right->left, tree.get_nil());
}

TEST_F(TestTree, TestRemove) {
  EXPECT_EQ(tree.get_root()->data->first, 13);
  tree.erase(13);
  EXPECT_EQ(tree.get_root()->data->first, 15);
  EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->data->first, 25);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->data->first, 17);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.size(), 9);

  tree.erase(11);
  EXPECT_EQ(tree.get_root()->data->first, 15);
  EXPECT_EQ(tree.get_root()->left->data->first, 6);
  EXPECT_EQ(tree.get_root()->left->left->data->first, 1);
  EXPECT_EQ(tree.get_root()->left->left->left, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->left->right, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->right->data->first, 8);
  EXPECT_EQ(tree.get_root()->left->right->left, tree.get_nil());
  EXPECT_EQ(tree.get_root()->left->right->right, tree.get_nil());
  EXPECT_EQ(tree.size(), 8);

  tree.erase(17);
  EXPECT_EQ(tree.get_root()->right->data->first, 25);
  EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
  EXPECT_EQ(tree.get_root()->right->left->data->first, 22);
  EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
  EXPECT_EQ(tree.get_root()->right->right->data->first, 27);
  EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
  EXPECT_EQ(tree.size(), 7);
}

TEST_F(TestTree, TestSize) {
  tree.size();
  EXPECT_EQ(tree.size(), 10);
}

TEST_F(TestTree, TestEmpty) {
  EXPECT_FALSE(tree.empty());
  ft::RedBlackTree<int, int> tree2;
  EXPECT_TRUE(tree2.empty());
}

TEST_F(TestTree, TestClear) {
  tree.clear();
  EXPECT_EQ(tree.get_root(), tree.get_nil());
}

TEST_F(TestTree, TestIterator) {
  ft::RedBlackTree<int, int>::iterator it = tree.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 1);
  ++it;
  EXPECT_EQ(it->first, 6);
  EXPECT_EQ(it->second, 6);
  ++it;
  EXPECT_EQ(it->first, 8);
  EXPECT_EQ(it->second, 8);
  ++it;
  EXPECT_EQ(it->first, 11);
  EXPECT_EQ(it->second, 11);
  ++it;
  EXPECT_EQ(it->first, 13);
  EXPECT_EQ(it->second, 13);
  ++it;
  EXPECT_EQ(it->first, 15);
  EXPECT_EQ(it->second, 15);
  ++it;
  EXPECT_EQ(it->first, 17);
  EXPECT_EQ(it->second, 17);
  ++it;
  EXPECT_EQ(it->first, 22);
  EXPECT_EQ(it->second, 22);
  ++it;
  EXPECT_EQ(it->first, 25);
  EXPECT_EQ(it->second, 25);
  ++it;
  EXPECT_EQ(it->first, 27);
  EXPECT_EQ(it->second, 27);
  ++it;
  EXPECT_EQ(it, tree.end());

  ft::RedBlackTree<int, int>::iterator it2 = tree.end();
  --it2;
  EXPECT_EQ(it2->first, 27);
  EXPECT_EQ(it2->second, 27);
  --it2;
  EXPECT_EQ(it2->first, 25);
  EXPECT_EQ(it2->second, 25);
  --it2;
  EXPECT_EQ(it2->first, 22);
  EXPECT_EQ(it2->second, 22);
  --it2;
  EXPECT_EQ(it2->first, 17);
  EXPECT_EQ(it2->second, 17);
  --it2;
  EXPECT_EQ(it2->first, 15);
  EXPECT_EQ(it2->second, 15);
  --it2;
  EXPECT_EQ(it2->first, 13);
  EXPECT_EQ(it2->second, 13);
  --it2;
  EXPECT_EQ(it2->first, 11);
  EXPECT_EQ(it2->second, 11);
  --it2;
  EXPECT_EQ(it2->first, 8);
  EXPECT_EQ(it2->second, 8);
  --it2;
  EXPECT_EQ(it2->first, 6);
  EXPECT_EQ(it2->second, 6);
  --it2;
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, 1);
  EXPECT_EQ(it2, tree.begin());
}

TEST_F(TestTree, TestReverseIterator) {
  ft::RedBlackTree<int, int>::reverse_iterator it = tree.rbegin();
  EXPECT_EQ(it->first, 27);
  EXPECT_EQ(it->second, 27);
  it++;
  EXPECT_EQ(it->first, 25);
  EXPECT_EQ(it->second, 25);
  it++;
  EXPECT_EQ(it->first, 22);
  EXPECT_EQ(it->second, 22);
  it++;
  EXPECT_EQ(it->first, 17);
  EXPECT_EQ(it->second, 17);
  it++;
  EXPECT_EQ(it->first, 15);
  EXPECT_EQ(it->second, 15);
  it++;
  EXPECT_EQ(it->first, 13);
  EXPECT_EQ(it->second, 13);
  it++;
  EXPECT_EQ(it->first, 11);
  EXPECT_EQ(it->second, 11);
  it++;
  EXPECT_EQ(it->first, 8);
  EXPECT_EQ(it->second, 8);
  it++;
  EXPECT_EQ(it->first, 6);
  EXPECT_EQ(it->second, 6);
  it++;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 1);
  it++;
  EXPECT_EQ(it, tree.rend());
}
