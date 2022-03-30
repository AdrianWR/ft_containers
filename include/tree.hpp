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
  typedef Alloc allocator_type;
  typedef enum color color_type;

  // Properties
  node_ptr parent;
  node_ptr left;
  node_ptr right;
  color_type color;
  pointer data;
  allocator_type alloc;

public:
  // Default Constructor
  explicit Node(color_type color = RED, node_ptr parent = _nullptr,
                node_ptr left = _nullptr, node_ptr right = _nullptr,
                allocator_type alloc = allocator_type())
      : data(_nullptr), parent(parent), left(left), right(right), color(color),
        alloc(alloc) {}

  // Value constructor
  Node(value_type v, color_type color, node_ptr nil,
       allocator_type alloc = allocator_type())
      : alloc(alloc), parent(nil), left(nil), right(nil), color(color) {
    data = alloc.allocate(1);
    alloc.construct(data, v);
  }

  // Copy constructor
  Node(const Node &n)
      : parent(n.parent), left(n.left), right(n.right), color(n.color),
        alloc(n.alloc), data(alloc.allocate(1)) {
    if (n.data != _nullptr) {
      alloc.construct(data, *n.data);
    }
  }

  // Copy assignment operator
  Node &operator=(const Node &node) {
    if (this != &node) {
      if (node.data != _nullptr) {
        if (data != _nullptr) {
          alloc.destroy(data);
          alloc.deallocate(data, 1);
        }
        data = alloc.allocate(1);
        alloc.construct(data, *node.data);
      } else {
        if (data != _nullptr) {
          alloc.destroy(data);
          alloc.deallocate(data, 1);
        }
        data = _nullptr;
      }
      parent = node.parent;
      left = node.left;
      right = node.right;
      color = node.color;
    }
    return *this;
  }

  // Default destructor
  virtual ~Node() {
    if (data != _nullptr) {
      alloc.destroy(data);
      alloc.deallocate(data, 1);
    }
  }

  // Getters

  // reference data() { return *data; }

  // const_reference data() const { return *data; }
};

template <class T>
class TreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;

  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef ft::ptrdiff_t difference_type;

  typedef TreeIterator<T> self;
  typedef typename Node<T>::node_ptr node_ptr;
  typedef Node<T> *link_type;

private:
  node_ptr _node;
  node_ptr _leaf;

public:
  TreeIterator() : _node(), _leaf() {}

  TreeIterator(node_ptr node, node_ptr leaf) : _node(node), _leaf(leaf) {}

  TreeIterator(const TreeIterator<T> &it) : _node(it._node), _leaf(it._leaf) {}

  self &operator=(const TreeIterator<T> &it) {
    if (this != &it) {
      _node = it._node;
      _leaf = it._leaf;
    }
    return *this;
  }

  reference operator*() const { return *_node->data; }

  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    node_ptr y;

    if (_node->right != _nullptr) {
      _node = _node->right;
      while (_node->left != _nullptr)
        _node = _node->left;
    } else {
      y = _node->parent;
      while (_node == y->right) {
        _node = y;
        y = y->parent;
      }
      if (_node->right != y)
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

    if (_node->color == ft::color::RED && _node->parent->parent == _node) {
      _node = _node->right;
    } else if (_node->left != _nullptr) {
      y = _node->left;
      while (y->right != _nullptr)
        y = y->right;
      _node = y;
    } else {
      y = _node->parent;
      while (_node == y->left) {
        _node = y;
        y = y->parent;
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

template <class T> class TreeConstIterator {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;

  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef ft::ptrdiff_t difference_type;

  typedef TreeConstIterator<T> self;
  typedef typename Node<T>::node_ptr node_ptr;
  typedef Node<T> *link_type;

private:
  node_ptr _node;
  node_ptr _leaf;

public:
  TreeConstIterator() : _node(), _leaf() {}

  TreeConstIterator(node_ptr node, node_ptr leaf = _nullptr)
      : _node(node), _leaf(leaf) {}

  TreeConstIterator(const TreeConstIterator<T> &it)
      : _node(it._node), _leaf(it._leaf) {}

  self &operator=(const TreeConstIterator<T> &it) {
    if (this != &it) {
      _node = it._node;
      _leaf = it._leaf;
    }
    return *this;
  }

  reference operator*() const { return *_node->data; }

  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    node_ptr y;

    if (_node->right != _nullptr) {
      _node = _node->right;
      while (_node->left != _nullptr)
        _node = _node->left;
    } else {
      y = _node->parent;
      while (_node == y->right) {
        _node = y;
        y = y->parent;
      }
      if (_node->right != y)
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

    if (_node->color == ft::color::RED && _node->parent->parent == _node) {
      _node = _node->right;
    } else if (_node->left != _nullptr) {
      y = _node->left;
      while (y->right != _nullptr)
        y = y->right;
      _node = y;
    } else {
      y = _node->parent;
      while (_node == y->left) {
        _node = y;
        y = y->parent;
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

  bool operator==(const self &it) const { return operator*() == *it; }

  bool operator!=(const self &it) const { return operator*() != *it; }
};

// template <class T>
// inline bool operator==(const TreeIterator<T> &it1,
//                        const TreeConstIterator<T> &it2) {
//   return *it1 == *it2;
// }
//
// template <class T>
// inline bool operator!=(const TreeIterator<T> &it1,
//                        const TreeConstIterator<T> &it2) {
//   return !(it1 == it2);
// }

template <class Key, class T, class Compare = ft::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T>>>
class RedBlackTree {
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const Key, T> value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef Alloc allocator_type;
  typedef Compare key_compare;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef Node<value_type, allocator_type> node_type;
  typedef node_type *node_ptr;
  typedef node_type &node_ref;
  typedef std::size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef TreeIterator<value_type> iterator;
  typedef TreeConstIterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::allocator<node_type> node_allocator_type;

private:
  node_ptr _root;
  node_ptr _nil;
  size_type _size;
  allocator_type _alloc;
  node_allocator_type _node_alloc;
  key_compare _comp;

public:
  // Default constructor
  explicit RedBlackTree(const key_compare &comp = key_compare(),
                        const allocator_type &alloc = allocator_type())
      : _node_alloc(node_allocator_type()), _alloc(alloc), _comp(comp),
        _size(0) {
    _nil = _new_nil_node();
    _root = _nil;
  }

  // Copy constructor
  RedBlackTree(const RedBlackTree &tree)
      : _node_alloc(node_allocator_type(tree._node_alloc)),
        _alloc(allocator_type(tree._alloc)), _comp(tree._comp),
        _size(tree._size) {
    _nil = _new_nil_node();
    _root = _copy_tree(tree._root, tree._nil);
  }

  // Destructor
  virtual ~RedBlackTree() {
    clear();
    _node_alloc.destroy(_nil);
    _node_alloc.deallocate(_nil, 1);
  }

  // Copy assignment operator
  RedBlackTree &operator=(const RedBlackTree &tree) {
    if (this != &tree) {
      _destroy_tree(_root);
      _root = _copy_tree(tree._root, tree._nil);
      _size = tree._size;
    }
    return *this;
  }

  // Getters

  node_ptr get_root() const { return _root; }

  node_ptr get_nil() const { return _nil; }

  // Capacity

  bool empty() const { return size() == 0; }

  size_type size() const { return _size; }

  size_type max_size() const { return size_type(-1); }

  // Iterators

  iterator begin() { return iterator(_minimum(_root), _nil); }

  iterator end() { return iterator(_nil, _nil); }

  const_iterator begin() const { return const_iterator(_minimum(_root), _nil); }

  const_iterator end() const { return const_iterator(_nil, _nil); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Tree operations

  /* @brief Inserts a new node with the given key and mapped value.
   *
   * @param value_type A pair of the key and the mapped value.
   * @return An iterator to the inserted node.
   *
   * Inserts a new node with the given key and value.
   * If the key already exists, the value is not updated.
   * For optimization, the non-existence of the key should be checked
   * on the caller function.
   */
  iterator insert_unique(const value_type &val) {
    node_ptr z = _new_node(val);
    _insert(z);
    _insert_fixup(z);
    ++_size;
    return iterator(z, _nil);
  }

  iterator insert_unique(iterator hint, const value_type &val) {
    (void)hint;
    return insert_unique(val);
  }

  void remove(const key_type &k) {
    node_ptr node = _find(k);
    if (node != _nil) {
      _remove(node);
      _node_alloc.destroy(node);
      _node_alloc.deallocate(node, 1);
      _size--;
    }
  }

  void clear() {
    _destroy_tree(_root);
    _root = _nil;
    _size = 0;
  }

private:
  // Private methods

  const key_type _key(node_ptr node) const { return node->data->first; }

  node_ptr _new_node(const value_type &value,
                     const typename node_type::color_type color = RED) {
    node_ptr z = _node_alloc.allocate(1);
    _node_alloc.construct(z, node_type(value, color, _nil, _alloc));
    return z;
  }

  node_ptr _new_nil_node() {
    node_ptr tmp = _node_alloc.allocate(1);
    _node_alloc.construct(tmp, node_type(BLACK));
    return tmp;
  }

  /* @brief Find the node with the given value
   * @param value The value to find
   * @return The node with the given value. If the value is not found,
   * return the nil node
   */
  node_ptr _find(const key_type &k) const {
    node_ptr node;

    node = _root;
    while (node != _nil) {
      if (!(_comp(k, _key(node)) || _comp(_key(node), k)))
        return node;
      else if (_comp(k, _key(node)))
        node = node->left;
      else
        node = node->right;
    }
    return _nil;
  }

  /* @brief Get the node with the minimum value in the subtree rooted at node.
   * @param node The root of the subtree.
   * @return The node with the minimum value in the subtree rooted at node.
   */
  node_ptr _minimum(node_ptr node) const {
    while (node->left != _nil) {
      node = node->left;
    }
    return node;
  }

  /* @brief Get the node with the maximum value in the subtree rooted at node.
   * @param node The root of the subtree.
   * @return The node with the maximum value in the subtree rooted at node.
   */
  node_ptr _maximum(node_ptr node) const {
    while (node->right != _nil) {
      node = node->right;
    }
    return node;
  }

  /*
   * @brief: Deep copy tree
   *
   * @param:
   *  node: root of the tree to copy
   *  nil: nil node of the tree to copy
   *
   * @return:
   *  root of the copied tree
   */
  node_ptr _copy_tree(const node_ptr &node, const node_ptr &tree_copy_nil) {
    if (node == tree_copy_nil)
      return _nil;
    node_ptr new_node = _node_alloc.allocate(1);
    _node_alloc.construct(new_node, *node);
    new_node->left = _copy_tree(node->left, tree_copy_nil);
    new_node->right = _copy_tree(node->right, tree_copy_nil);
    new_node->parent = _nil;
    if (new_node->left != _nil)
      new_node->left->parent = new_node;
    if (new_node->right != _nil)
      new_node->right->parent = new_node;
    return new_node;
  }

  /*
   * @brief: Destroy tree
   *
   * @param:
   *  node: root of the tree to destroy
   *
   *  Destroy nodes and deallocate all tree memory
   */
  void _destroy_tree(node_ptr node) {
    if (node != _nil) {
      _destroy_tree(node->left);
      _destroy_tree(node->right);
      _node_alloc.destroy(node);
      _node_alloc.deallocate(node, 1);
    }
  }

  /* @brief Removes the node z from the tree.
   *
   * @param z The node to be removed.
   *
   * At the end of the deletion, the node z is removed from the tree,
   * and the tree is rebalanced, accordingly to the Red Black Tree
   * properties.
   */
  void _remove(node_ptr z) {
    node_ptr x;
    node_ptr y = z;
    color y_original_color = y->color;
    if (z->left == _nil) {
      x = z->right;
      _transplant(z, z->right);
    } else if (z->right == _nil) {
      x = z->left;
      _transplant(z, z->left);
    } else {
      y = _minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        _transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      _transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    if (y_original_color == BLACK) {
      _remove_fixup(x);
    }
  }

  void _remove_fixup(node_ptr x) {
    node_ptr w;
    while (x != _root && x->color == BLACK) {
      if (x == x->parent->left) {
        w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          _left_rotate(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          _right_rotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        _left_rotate(x->parent);
        x = _root;
      } else {
        w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          _right_rotate(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          _left_rotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        _right_rotate(x->parent);
        x = _root;
      }
    }
    x->color = BLACK;
  }

  /* @brief Transplant node z with node y
   * @param z node to be transplanted
   * @param y node to be transplanted to
   *
   * The child nodes of y are transplanted to z as well.
   * If y is the root, the root is changed to z.
   */

  void _transplant(node_ptr u, node_ptr v) {
    if (u->parent == _nil) {
      _root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  /* @brief Inserts a node into the tree.
   *
   * @param z The node to be inserted.
   *
   * This function is called by public method insert().
   * The value of z is inserted into the tree, and its lacking
   * is checked before calling this function.
   *
   *
   *   p                           p
   *  / \                         / \
   * l   q                       l   q
   *    / \   =>                /   / \
   *   p   r                   z   l   q
   *
   */

  void _insert(node_ptr z) {
    node_ptr y = _nil;
    node_ptr x = _root;
    while (x != _nil) {
      y = x;
      if (_comp(_key(z), _key(x)))
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == _nil)
      _root = z;
    else if (_comp(_key(z), _key(y)))
      y->left = z;
    else
      y->right = z;
  }

  void _insert_fixup(node_ptr z) {
    while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        node_ptr y = z->parent->parent->right;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            _left_rotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          _right_rotate(z->parent->parent);
        }
      } else {
        node_ptr y = z->parent->parent->left;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            _right_rotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          _left_rotate(z->parent->parent);
        }
      }
    }
    _root->color = BLACK;
  }

  /* @brief Left Rotate
   *
   * @param[in] x node to rotate
   *
   *   p                           q
   *  / \                          / \
   * l   q                        p   r
   *    / \   =>                  / \
   *   p   r                      l   q
   *
   * Executes a left rotation on the node x.
   * The rotation is performed such that the node x becomes the left child of
   * its right child. The right child is returned as the result of the
   * rotation. The rotation is performed in-place. The color of x is
   * preserved.
   */
  void _left_rotate(node_ptr x) {
    node_ptr y = x->right;
    x->right = y->left;
    if (y->left != _nil)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == _nil)
      _root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  /* @brief Right Rotate
   *
   * @param[in] x node to rotate
   *
   * Executes a right rotation on the node x.
   * The rotation is performed such that the node x becomes the right child of
   * its left child. The left child is returned as the result of the rotation.
   * The rotation is performed in-place. The color of x is preserved.
   */
  void _right_rotate(node_ptr x) {
    node_ptr y = x->left;
    x->left = y->right;
    if (y->right != _nil)
      y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == _nil)
      _root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }
};

template <class Key, class T>
inline bool operator==(const RedBlackTree<Key, T> &lhs,
                       const RedBlackTree<Key, T> &rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T>
inline bool operator!=(const RedBlackTree<Key, T> &lhs,
                       const RedBlackTree<Key, T> &rhs) {
  return !(lhs == rhs);
}

} // namespace ft

#endif
