#ifndef TREE_HPP
#define TREE_HPP

#include "functional.hpp"
#include "iterator.hpp"
#include "nullptr.hpp"
#include "utility.hpp"
#include <cstddef>
#include <memory>

#include <iostream>

namespace ft {

enum color { RED, BLACK };

template <class T, class Alloc = std::allocator<T>> class Node {
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
  typedef Alloc allocator_type;

private:
  // Properties
  node_ptr _parent;
  node_ptr _left;
  node_ptr _right;
  enum color _color;
  pointer _value_ptr;
  allocator_type _alloc;

public:
  // Default Constructor
  explicit Node(node_ptr parent = _nullptr, node_ptr left = _nullptr,
                node_ptr right = _nullptr, enum color color = RED,
                allocator_type alloc = allocator_type())
      : _value_ptr(_nullptr), _parent(parent), _left(left), _right(right),
        _color(color), _alloc(alloc) {}

  // Value constructor
  Node(value_type value, enum color color = RED, node_ptr parent = _nullptr,
       node_ptr left = _nullptr, node_ptr right = _nullptr,
       allocator_type alloc = allocator_type())
      : _parent(parent), _left(left), _right(right), _color(color) {
    _value_ptr = _alloc.allocate(1);
    _alloc.construct(_value_ptr, value);
  }

  // Copy constructor
  Node(const Node &other)
      : _value_ptr(_nullptr), _parent(other._parent), _left(other._left),
        _right(other._right), _color(other._color), _alloc(other._alloc) {
    if (other._value_ptr != _nullptr) {
      _value_ptr = _alloc.allocate(1);
      _alloc.construct(_value_ptr, *other._value_ptr);
    }
  }

  // Copy assignment operator
  Node &operator=(const Node &other) {
    if (this != &other) {
      if (other._value_ptr != _nullptr) {
        if (_value_ptr != _nullptr) {
          _alloc.destroy(_value_ptr);
          _alloc.deallocate(_value_ptr, 1);
        }
        _value_ptr = _alloc.allocate(1);
        _alloc.construct(_value_ptr, *other._value_ptr);
      } else {
        if (_value_ptr != _nullptr) {
          _alloc.destroy(_value_ptr);
          _alloc.deallocate(_value_ptr, 1);
        }
        _value_ptr = _nullptr;
      }
      _parent = other._parent;
      _left = other._left;
      _right = other._right;
      _color = other._color;
    }
    return *this;
  }

  // Default destructor
  virtual ~Node() {
    if (_value_ptr != _nullptr) {
      _alloc.destroy(_value_ptr);
      _alloc.deallocate(_value_ptr, 1);
    }
  }

  // Getters

  reference value() { return *_value_ptr; }

  const_reference value() const { return *_value_ptr; }

  node_ptr parent() { return _parent; }

  const_node_ptr parent() const { return _parent; }

  node_ptr left() { return _left; }

  const_node_ptr left() const { return _left; }

  node_ptr right() { return _right; }

  const_node_ptr right() const { return _right; }

  enum color color() { return _color; }

  const_node_ptr color() const { return _color; }

  // Setters

  void value(value_type value) {
    if (_value_ptr == _nullptr) {
      _value_ptr = _alloc.allocate(1);
    } else {
      _alloc.destroy(_value_ptr);
    }
    _alloc.construct(_value_ptr, value);
  }

  void left(node_ptr left) { _left = left; }

  void right(node_ptr right) { _right = right; }

  void parent(node_ptr parent) { _parent = parent; }

  node_ptr next() {
    node_ptr x;
    node_ptr y;
    x = this;

    if (x->right() != _nullptr) {
      x = x->right();
      while (x->left() != _nullptr)
        x = x->left();
    } else {
      y = x->parent();
      while (x == y->right()) {
        x = y;
        y = y->parent();
      }
      if (x->right() != y)
        x = y;
    }
    return x;
  }

  node_ptr previous() {
    node_ptr x;
    node_ptr y;
    x = this;

    if (x->color() == ft::color::RED && x->parent()->parent() == x) {
      x = x->right();
    } else if (x->left() != _nullptr) {
      y = x->left();
      while (y->right() != _nullptr)
        y = y->right();
      x = y;
    } else {
      y = x->parent();
      while (x == y->left()) {
        x = y;
        y = y->parent();
      }
      x = y;
    }
    return x;
  }

  node_ptr minimum() {
    node_ptr x = this;
    while (x->left() != _nullptr) {
      x = x->left();
    }
    return x;
  }

  node_ptr maximum() {
    node_ptr x = this;
    while (x->right() != _nullptr)
      x = x->right();
    return x;
  }

  // Comparison operators
  // bool operator==(const Node &node) const { return _value == node.value; }

  // bool operator!=(const Node &node) const { return value != node.value; }

  // bool operator<(const Node &node) const { return value < node.value; }

  // bool operator>(const Node &node) const { return value > node.value; }

  // bool operator<=(const Node &node) const { return value <= node.value; }

  // bool operator>=(const Node &node) const { return value >= node.value; }
};

template <class T> bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
  return lhs.value == rhs.value;
}

template <class T> bool operator!=(const Node<T> &lhs, const Node<T> &rhs) {
  return !(lhs == rhs);
}

template <class T> bool operator<(const Node<T> &lhs, const Node<T> &rhs) {
  return lhs.get_value() < rhs.get_value();
}

template <class T> bool operator>(const Node<T> &lhs, const Node<T> &rhs) {
  return lhs.get_value() > rhs.get_value();
}

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

  reference operator*() const { return _node->value; }

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

template <class T, class Compare = ft::less<T>, class Node = Node<T>,
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
  typedef RBTreeIterator<T> iterator;
  typedef RBTreeIterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  node_ptr _root;
  allocator_type _alloc;
  node_allocator_type _node_alloc;

public:
  // Default constructor
  explicit RedBlackTree(
      const node_allocator_type &node_alloc = node_allocator_type(),
      const allocator_type &alloc = allocator_type())
      : _node_alloc(node_alloc), _alloc(alloc) {
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root, _nullptr, _nullptr, _nullptr, ft::color::BLACK,
                          _alloc);
  }

  // Value constructor
  explicit RedBlackTree(
      const value_type &value,
      const node_allocator_type &node_alloc = node_allocator_type(),
      const allocator_type &alloc = allocator_type())
      : _node_alloc(node_alloc) {
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root, node_type(value, _nullptr, _nullptr, _nullptr,
                                           ft::color::BLACK, _alloc));
  }

  // Copy constructor
  // RedBlackTree(const RedBlackTree &tree)
  //    : _node_alloc(tree._node_alloc), _alloc(tree._alloc) {
  //  _root = _node_alloc.allocate(1);
  //  _node_alloc.construct(_root, _nullptr, _nullptr, _nullptr,
  //  ft::color::BLACK,
  //                        _alloc);
  //  for (const_iterator it = tree.begin(); it != tree.end(); ++it) {
  //    insert(*it);
  //  }
  //}

  // Destructor
  virtual ~RedBlackTree() {}

  //// Copy assignment operator
  // RedBlackTree &operator=(const RedBlackTree &tree) {
  //   if (this != &tree) {
  //     _node_alloc = tree._node_alloc;
  //     _root = tree._root;
  //   }
  //   return *this;
  // }

  // Getters

  node_ptr get_root() const { return _root; }

  node_ptr get_nil() const { return _nullptr; }

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
      if (z->value < x->value)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == _nullptr)
      _root = z;
    else if (z->value < y->value)
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
