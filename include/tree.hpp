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
  explicit Node(enum color color = RED, node_ptr parent = _nullptr,
                node_ptr left = _nullptr, node_ptr right = _nullptr,
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

  void set_left(node_ptr left) { _left = left; }

  void set_right(node_ptr right) { _right = right; }

  void set_parent(node_ptr parent) { _parent = parent; }

  void set_color(enum color color) { _color = color; }

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
class NodeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
  typedef T value_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator<iterator_category, T>::pointer pointer;
  typedef typename ft::iterator<iterator_category, T>::reference reference;
  typedef typename ft::iterator<iterator_category, T>::difference_type
      difference_type;
  typedef Node<value_type> node_type;
  typedef Node<value_type> *node_ptr;
  typedef Node<value_type> &node_ref;
  typedef NodeIterator<value_type> self;

private:
  node_ptr _node;
  node_ptr _leaf;

public:
  NodeIterator() : _node(), _leaf() {}

  NodeIterator(node_ptr node, node_ptr leaf = _nullptr)
      : _node(node), _leaf(leaf) {}

  NodeIterator(const NodeIterator<T> &it) : _node(it._node), _leaf(it._leaf) {}

  NodeIterator<T> &operator=(const NodeIterator<T> &it) {
    if (this != &it) {
      _node = it._node;
      _leaf = it._leaf;
    }
    return *this;
  }

  reference operator*() const { return _node->value(); }

  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    node_ptr y;

    if (_node->right() != _nullptr) {
      _node = _node->right();
      while (_node->left() != _nullptr)
        _node = _node->left();
    } else {
      y = _node->parent();
      while (_node == y->right()) {
        _node = y;
        y = y->parent();
      }
      if (_node->right() != y)
        _node = y;
    }
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self &operator--() {
    node_ptr y;

    if (_node->color() == ft::color::RED &&
        _node->parent()->parent() == _node) {
      _node = _node->right();
    } else if (_node->left() != _nullptr) {
      y = _node->left();
      while (y->right() != _nullptr)
        y = y->right();
      _node = y;
    } else {
      y = _node->parent();
      while (_node == y->left()) {
        _node = y;
        y = y->parent();
      }
      _node = y;
    }
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
  typedef NodeIterator<T> iterator;
  typedef NodeIterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  node_ptr _root;
  node_ptr _nil;
  allocator_type _alloc;
  node_allocator_type _node_alloc;
  key_compare _comp;

public:
  // Default constructor
  explicit RedBlackTree(
      const node_allocator_type &node_alloc = node_allocator_type(),
      const allocator_type &alloc = allocator_type())
      : _node_alloc(node_alloc), _alloc(alloc) {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node_type(BLACK));
    _root = _nil;
  }

  // Value constructor
  explicit RedBlackTree(
      const value_type &value,
      const node_allocator_type &node_alloc = node_allocator_type(),
      const allocator_type &alloc = allocator_type())
      : _node_alloc(node_alloc) {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node_type(BLACK));
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root,
                          node_type(value, BLACK, _nil, _nil, _nil, _alloc));
  }

  // Copy constructor
  RedBlackTree(const RedBlackTree &tree)
      : _node_alloc(tree._node_alloc), _alloc(tree._alloc) {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node_type(BLACK));
    _root = _node_alloc.allocate(1);
    _node_alloc.construct(_root, node_type(BLACK, _nil, _nil, _nil, _alloc));
    for (const_iterator it = tree.begin(); it != tree.end(); ++it) {
      insert(*it);
    }
  }

  void _deallocate_tree(node_ptr node) {
    if (node != _nil) {
      _deallocate_tree(node->left());
      _deallocate_tree(node->right());
      _node_alloc.destroy(node);
      _node_alloc.deallocate(node, 1);
    }
  }

  // Destructor
  virtual ~RedBlackTree() {
    _deallocate_tree(_root);
    _node_alloc.destroy(_nil);
    _node_alloc.deallocate(_nil, 1);
  }

  //// Copy assignment operator
  // RedBlackTree &operator=(const RedBlackTree &tree) {
  //   if (this != &tree) {
  //     _node_alloc = tree._node_alloc;
  //     _root = tree._root;
  //   }
  //   return *this;
  // }

  // Iterators

  iterator begin() {
    node_ptr node = _root;
    while (node->left() != _nil) {
      node = node->left();
    }
    return iterator(node, _nil);
  }

  const_iterator begin() const { return const_iterator(begin()); }

  iterator end() {
    node_ptr node = _root;
    while (node->right() != _nil) {
      node = node->right();
    }
    return iterator(node, _nil);
  }

  const_iterator end() const { return const_iterator(end()); }

  // Getters

  node_ptr get_root() const { return _root; }

  node_ptr get_nil() const { return _nil; }

  // Tree operations

  void insert(const value_type &value) {
    node_ptr z = _node_alloc.allocate(1);
    if (_root == _nil) {
      _node_alloc.construct(z,
                            node_type(value, BLACK, _nil, _nil, _nil, _alloc));
      _root = z;
    } else {
      _node_alloc.construct(z, node_type(value, RED, _nil, _nil, _nil, _alloc));
      _insert(z);
      _insert_fixup(z);
    }
  }

  node_ptr _find_node(const value_type &value) const {
    node_ptr node = _root;
    while (node != _nil) {
      if (node->value() == value) {
        return node;
      } else if (value < node->value()) {
        node = node->left();
      } else {
        node = node->right();
      }
    }
    return _nil;
  }

  iterator find(const value_type &value) {
    node_ptr node = _find_node(value);
    if (node == _nil)
      return end();
    return iterator(node, _nil);
  }

  const_iterator find(const value_type &value) const {
    return const_iterator(find(value));
  }

  void remove(const value_type &value) {
    node_ptr node = _find_node(value);
    if (node != _nil) {
      _remove(node);
      _node_alloc.destroy(node);
      _node_alloc.deallocate(node, 1);
    }
  }

private:
  void _remove(node_ptr z) {
    node_ptr x;
    node_ptr y = z;
    color y_original_color = y->color();
    if (z->left() == _nil) {
      x = z->right();
      _transplant(z, z->right());
    } else if (z->right() == _nil) {
      x = z->left();
      _transplant(z, z->left());
    } else {
      y = _minimum(z->right());
      y_original_color = y->color();
      x = y->right();
      if (y->parent() == z) {
        x->set_parent(y);
      } else {
        _transplant(y, y->right());
        y->set_right(z->right());
        y->right()->set_parent(y);
      }
      _transplant(z, y);
      y->set_left(z->left());
      y->left()->set_parent(y);
      y->set_color(z->color());
    }
    if (y_original_color == BLACK) {
      _remove_fixup(x);
    }
  }

  void _remove_fixup(node_ptr x) {
    node_ptr w;
    while (x != _root && x->color() == BLACK) {
      if (x == x->parent()->left()) {
        w = x->parent()->right();
        if (w->color() == RED) {
          w->set_color(BLACK);
          x->parent()->set_color(RED);
          _left_rotate(x->parent());
          w = x->parent()->right();
        }
        if (w->left()->color() == BLACK && w->right()->color() == BLACK) {
          w->set_color(RED);
          x = x->parent();
        } else if (w->right()->color() == BLACK) {
          w->left()->set_color(BLACK);
          w->set_color(RED);
          _right_rotate(w);
          w = x->parent()->right();
        }
        w->set_color(x->parent()->color());
        x->parent()->set_color(BLACK);
        w->right()->set_color(BLACK);
        _left_rotate(x->parent());
        x = _root;
      } else {
        w = x->parent()->left();
        if (w->color() == RED) {
          w->set_color(BLACK);
          x->parent()->set_color(RED);
          _right_rotate(x->parent());
          w = x->parent()->left();
        }
        if (w->right()->color() == BLACK && w->left()->color() == BLACK) {
          w->set_color(RED);
          x = x->parent();
        } else if (w->left()->color() == BLACK) {
          w->right()->set_color(BLACK);
          w->set_color(RED);
          _left_rotate(w);
          w = x->parent()->left();
        }
        w->set_color(x->parent()->color());
        x->parent()->set_color(BLACK);
        w->left()->set_color(BLACK);
        _right_rotate(x->parent());
        x = _root;
      }
    }
    x->set_color(BLACK);
  }

  node_ptr _minimum(node_ptr z) const {
    while (z->left() != _nil) {
      z = z->left();
    }
    return z;
  }

  void _transplant(node_ptr u, node_ptr v) {
    if (u->parent() == _nil) {
      _root = v;
    } else if (u == u->parent()->left()) {
      u->parent()->set_left(v);
    } else {
      u->parent()->set_right(v);
    }
    v->set_parent(u->parent());
  }

  void _insert(node_ptr z) {
    node_ptr y = _nil;
    node_ptr x = _root;
    while (x != _nil) {
      y = x;
      if (_comp(z->value(), x->value()))
        x = x->left();
      else
        x = x->right();
    }
    z->set_parent(y);
    if (y == _nil)
      _root = z;
    else if (_comp(z->value(), y->value()))
      y->set_left(z);
    else
      y->set_right(z);
  }

  void _insert_fixup(node_ptr z) {
    while (z->parent()->color() == RED) {
      if (z->parent() == z->parent()->parent()->left()) {
        node_ptr y = z->parent()->parent()->right();
        if (y->color() == RED) {
          z->parent()->set_color(BLACK);
          y->set_color(BLACK);
          z->parent()->parent()->set_color(RED);
          z = z->parent()->parent();
        } else {
          if (z == z->parent()->right()) {
            z = z->parent();
            _left_rotate(z);
          }
          z->parent()->set_color(BLACK);
          z->parent()->parent()->set_color(RED);
          _right_rotate(z->parent()->parent());
        }
      } else {
        node_ptr y = z->parent()->parent()->left();
        if (y->color() == RED) {
          z->parent()->set_color(BLACK);
          y->set_color(BLACK);
          z->parent()->parent()->set_color(RED);
          z = z->parent()->parent();
        } else {
          if (z == z->parent()->left()) {
            z = z->parent();
            _right_rotate(z);
          }
          z->parent()->set_color(BLACK);
          z->parent()->parent()->set_color(RED);
          _left_rotate(z->parent()->parent());
        }
      }
    }
    _root->set_color(BLACK);
  }

  void _left_rotate(node_ptr x) {
    node_ptr y = x->right();
    x->set_right(y->left());
    if (y->left() != _nil)
      y->left()->set_parent(x);
    y->set_parent(x->parent());
    if (x->parent() == _nil)
      _root = y;
    else if (x == x->parent()->left())
      x->parent()->set_left(y);
    else
      x->parent()->set_right(y);
    y->set_left(x);
    x->set_parent(y);
  }

  void _right_rotate(node_ptr x) {
    node_ptr y = x->left();
    x->set_left(y->right());
    if (y->right() != _nil)
      y->right()->set_parent(x);
    y->set_parent(x->parent());
    if (x->parent() == _nil)
      _root = y;
    else if (x == x->parent()->right())
      x->parent()->set_right(y);
    else
      x->parent()->set_left(y);
    y->set_right(x);
    x->set_parent(y);
  }
};

} // namespace ft

#endif
