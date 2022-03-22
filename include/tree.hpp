#ifndef TREE_HPP
#define TREE_HPP

#include "functional.hpp"
#include "iterator.hpp"
#include "nullptr.hpp"
#include "utility.hpp"
#include <cstddef>
#include <memory>

namespace ft {

enum color { RED, BLACK };
template <class T> class Node {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef Node<T> *node_ptr;
  typedef Node<T> &node_ref;
  typedef const Node<T> *const_node_ptr;
  typedef const Node<T> &const_node_ref;

private:
  value_type _value;
  node_ptr _parent;
  node_ptr _left;
  node_ptr _right;
  color _color;

public:
  node_ptr next() {
    pointer x = this;
    if (x->right != nullptr) {
      x = x->right;
      while (x->left != nullptr)
        x = x->left;
    } else {
      pointer y = x->parent;
      while (x == y->right) {
        x = y;
        y = y->parent;
      }
      if (x->right != y)
        x = y;
    }
    return x;
  }

  node_ptr previous() {
    pointer x = this;
    if (x->color == ft::color::RED && x->parent->parent == x) {
      x = x->right;
    } else if (x->left != nullptr) {
      pointer y = x->left;
      while (y->right != nullptr)
        y = y->right;
      x = y;
    } else {
      pointer y = x->parent;
      while (x == y->left) {
        x = y;
        y = y->parent;
      }
      x = y;
    }
    return x;
  }

  // Default constructor
  Node()
      : _parent(_nullptr), _left(_nullptr), _right(_nullptr), _color(BLACK) {}

  // Constructor
  Node(node_ptr parent = _nullptr, node_ptr left = _nullptr,
       node_ptr right = _nullptr, color color = RED)
      : _parent(parent), _left(left), _right(right), _color(color) {}

  // Value constructor
  Node(value_type value, node_ptr parent = _nullptr, node_ptr left = _nullptr,
       node_ptr right = _nullptr, color color = RED)
      : _value(value), _parent(parent), _left(left), _right(right),
        _color(color) {}

  // Copy constructor
  Node(const Node &node) {
    _value = node._value;
    _parent = node._parent;
    _left = node._left;
    _right = node._right;
    _color = node._color;
  }

  // Copy assignment operator
  Node &operator=(const Node &node) {
    if (this != &node) {
      _value = node._value;
      _parent = node._parent;
      _left = node._left;
      _right = node._right;
    }
    return *this;
  };

  // Default destructor
  virtual ~Node() {}

  // Comparison operators
  bool operator==(const Node &node) const { return _value == node._value; }

  bool operator!=(const Node &node) const { return _value != node._value; }

  bool operator<(const Node &node) const { return _value < node._value; }

  bool operator>(const Node &node) const { return _value > node._value; }

  bool operator<=(const Node &node) const { return _value <= node._value; }

  bool operator>=(const Node &node) const { return _value >= node._value; }

  // Getters

  value_type get_value() const { return _value; }

  node_ptr get_parent() const { return _parent; }

  node_ptr get_left() const { return _left; }

  node_ptr get_right() const { return _right; }

  color get_color() const { return _color; }
};

template <class T>
class RBTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
  typedef T value_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator<iterator_category, T>::pointer pointer;
  typedef typename ft::iterator<iterator_category, T>::reference reference;
  typedef typename ft::iterator<iterator_category, T>::difference_type
      difference_type;
  typedef RBTreeIterator<T> self;
  typedef Node<T> node_type;

private:
  node_type _node;

public:
  RBTreeIterator() : _node() {}

  RBTreeIterator(node_type node) : _node(node) {}

  reference operator*() const { return _node->_value; }

  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    _node = _node->next();
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self &operator--() {
    _node = _node->previous();
    return *this;
  }

  self operator--(int) {
    self tmp = *this;
    --*this;
    return tmp;
  }

  bool operator==(const self &it) const { return _node == it._node; }

  bool operator!=(const self &it) const { return _node != it._node; }
};

template <class T, class Compare = ft::less<T>, class Node = ft::Node<T>,
          class Alloc = std::allocator<T>,
          class NodeAlloc = std::allocator<Node>>
class RedBlackTree {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef Node node_type;
  typedef Node *node_ptr;
  typedef Node &node_ref;
  typedef const Node *const_node_ptr;
  typedef const Node &const_node_ref;
  typedef Alloc allocator_type;
  typedef NodeAlloc node_allocator_type;
  typedef Compare key_compare;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

private:
  node_ptr _root;
  node_allocator_type _node_alloc;
  static node_ptr _nil = Node();

public:
  // Default constructor
  RedBlackTree(const node_allocator_type &node_alloc = node_allocator_type())
      : _node_alloc(node_alloc) {
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root, _nullptr, _nullptr, _nullptr);
  }

  // Copy constructor
  RedBlackTree(const RedBlackTree &tree) : _node_alloc(tree._node_alloc) {
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root, _nullptr, _nullptr, _nullptr);
    _root = tree._root;
  }

  // Destructor
  virtual ~RedBlackTree() {
    _node_alloc.destroy(_root);
    _node_alloc.deallocate(_root, 1);
  }

  // Copy assignment operator
  RedBlackTree &operator=(const RedBlackTree &tree) {
    if (this != &tree) {
      _node_alloc = tree._node_alloc;
      _root = tree._root;
    }
    return *this;
  }

  void left_rotate(node_ptr x) {
    node_ptr y = x->right;
    x->right = y->left;
    if (y->left != _nullptr)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == _nullptr)
      _root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void right_rotate(node_ptr x) {
    node_ptr y = x->left;
    x->left = y->right;
    if (y->right != _nullptr)
      y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == _nullptr)
      _root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->right = x;
    x->parent = y;
  }

  void insert(node_ptr z) {
    if (z == _nullptr)
      return;
    node_ptr y = _nullptr;
    node_ptr x = _root;
    while (x != _nullptr) {
      y = x;
      if (z->_value < x->_value)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == _nullptr)
      _root = z;
    else if (z->_value < y->_value)
      y->left = z;
    else
      y->right = z;
    z->left = _nullptr;
    z->right = _nullptr;
    z->color = RED;
    insert_fixup(z);
  }

  void insert_fixup(node_ptr z) {
    while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        node_ptr y = z->parent->parent->right;
      };
      if (z->parent == z->parent->parent->right) {
        node_ptr y = z->parent->parent->left;
      };
      if (z->parent->parent->color == RED) {
        z->parent->color = BLACK;
        z->parent->parent->color = BLACK;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        right_rotate(z->parent->parent);
      }
    }
    _root->color = BLACK;
  }

  void erase(node_ptr z) {
    node_ptr y = z;
    node_ptr x = _nullptr;
    node_ptr x_parent = _nullptr;
    if (z->left == _nullptr) {
      x = z->right;
      x_parent = z->parent;
    } else if (z->right == _nullptr) {
      x = z->left;
      x_parent = z->parent;
    } else {
      y = z->right;
      while (y->left != _nullptr)
        y = y->left;
      x = y->right;
      x_parent = y->parent;
      if (y->parent == z)
        x_parent = y;
      else {
        x_parent->left = x;
        if (x != _nullptr)
          x->parent = x_parent;
      }
      y->parent = z->parent;
      if (z->parent == _nullptr)
        _root = y;
      else if (z == z->parent->left)
        z->parent->left = y;
      else
        z->parent->right = y;
      y->left = z->left;
      y->right = z->right;
      y->color = z->color;
    }
    if (y->color == BLACK)
      erase_fixup(x, x_parent);
  }
};

} // namespace ft

#endif
