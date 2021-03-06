#ifndef TREE_HPP
#define TREE_HPP

#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "nullptr.hpp"
#include "utility.hpp"
#include <cstddef>
#include <memory>

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
  node_ptr aux;
  color_type color;
  pointer data;
  allocator_type alloc;

public:
  // Default Constructor
  explicit Node(color_type color = BLACK, node_ptr parent = _nullptr,
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
        alloc(n.alloc) {
    data = alloc.allocate(1);
    if (n.data != _nullptr)
      alloc.construct(data, *n.data);
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
    }
    alloc.deallocate(data, 1);
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

  node_ptr _node;

private:
  node_ptr _leaf;

public:
  TreeIterator() : _node() {}

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

  node_ptr _minimum(node_ptr node) {
    while (node->left != _leaf)
      node = node->left;
    return node;
  }

  node_ptr _maximum(node_ptr node) {
    while (node->right != _leaf)
      node = node->right;
    return node;
  }

  node_ptr _successor(node_ptr x) {
    if (x->right != _leaf)
      return _minimum(x->right);
    node_ptr y = x->parent;
    while (y != _leaf && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  node_ptr _predecessor(node_ptr x) {
    if (x == _leaf) {
      return _leaf->aux;
    }
    if (x->left != _leaf)
      return _maximum(x->left);
    node_ptr y = x->parent;
    while (y != _leaf && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  self &operator++() {
    _node = _successor(_node);
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self &operator--() {
    _node = _predecessor(_node);
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

  node_ptr _node;

private:
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

  node_ptr _minimum(node_ptr node) {
    while (node->left != _leaf)
      node = node->left;
    return node;
  }

  node_ptr _maximum(node_ptr node) {
    while (node->right != _leaf)
      node = node->right;
    return node;
  }

  node_ptr _successor(node_ptr x) {
    if (x->right != _leaf)
      return _minimum(x->right);
    node_ptr y = x->parent;
    while (y != _leaf && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  node_ptr _predecessor(node_ptr x) {
    if (x == _leaf) {
      return _leaf->aux;
    }
    if (x->left != _leaf)
      return _maximum(x->left);
    node_ptr y = x->parent;
    while (y != _leaf && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  self &operator++() {
    _node = _successor(_node);
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self &operator--() {
    _node = _predecessor(_node);
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

template <class T>
inline bool operator==(const TreeIterator<T> &it1,
                       const TreeConstIterator<T> &it2) {
  return *it1 == *it2;
}

template <class T>
inline bool operator!=(const TreeIterator<T> &it1,
                       const TreeConstIterator<T> &it2) {
  return !(it1 == it2);
}

template <class Key, class T, class KeyOfValue, class Compare = ft::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T>>>
class RedBlackTree {
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef typename Alloc::value_type value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef Alloc allocator_type;
  typedef Compare key_compare;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef Node<value_type, allocator_type> node_type;
  typedef node_type *node_ptr;
  typedef node_type const &node_ref;
  typedef std::size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef TreeIterator<value_type> iterator;
  typedef TreeConstIterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::allocator<node_type> node_allocator_type;

private:
  size_type _size;
  allocator_type _alloc;
  node_allocator_type _node_alloc;
  key_compare _comp;

  // Aux Nodes
  node_ptr _root;
  node_ptr _nil;

public:
  // Default constructor
  explicit RedBlackTree(const key_compare &comp = key_compare(),
                        const allocator_type &alloc = allocator_type())
      : _node_alloc(node_allocator_type()), _alloc(alloc), _comp(comp),
        _size(0) {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node_type());
    _nil->parent = _nil->left = _nil->right = _nil;
    _root = _nil;
  }

  // Copy constructor
  RedBlackTree(const RedBlackTree &tree)
      : _node_alloc(node_allocator_type(tree._node_alloc)),
        _alloc(allocator_type(tree._alloc)), _comp(tree._comp),
        _size(tree._size) {
    _nil = _node_alloc.allocate(1);
    _nil->parent = _nil->left = _nil->right = _nil;
    _node_alloc.construct(_nil, node_type());
    _root = _copy_tree(tree._root, tree._nil);
    _nil->aux = _maximum(_root);
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

  const_iterator begin() const { return const_iterator(_minimum(_root), _nil); }

  iterator end() { return iterator(_nil, _nil); }

  const_iterator end() const { return const_iterator(_nil, _nil); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Tree operations

  ft::pair<iterator, bool> insert_unique(const value_type &val) {
    return _insert(val);
  }

  iterator insert_unique(iterator hint, const value_type &val) {
    (void)hint;
    ft::pair<iterator, bool> p = _insert(val);
    return p.first;
  }

  template <class InputIterator>
  void insert_unique(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      _insert(*first);
    }
  }

  void erase(iterator position) {
    if (position == end())
      return;
    _erase_aux(position);
  }

  size_type erase(const key_type &key) {
    ft::pair<iterator, iterator> p = equal_range(key);
    const size_type old_size = size();
    _erase_aux(p.first, p.second);
    return old_size - size();
  }

  void erase(iterator first, iterator last) { _erase_aux(first, last); }

  void swap(RedBlackTree &tree) {
    RedBlackTree<Key, T, KeyOfValue, Compare, Alloc> tmp(tree);
    tree = *this;
    *this = tmp;
  }

  void clear() {
    _destroy_tree(_root);
    _root = _nil;
    _size = 0;
  }

  key_compare key_comp() const { return _comp; }

  iterator find(const key_type &key) {
    node_ptr node = _find(key);
    return iterator(node, _nil);
  }

  const_iterator find(const key_type &key) const {
    node_ptr node = _find(key);
    return const_iterator(node, _nil);
  }

  size_type count(const key_type &key) const {
    return _find(key) == _nil ? 0 : 1;
  }

  iterator lower_bound(const key_type &key) {
    return iterator(_lower_bound(key), _nil);
  }

  const_iterator lower_bound(const key_type &key) const {
    return const_iterator(_lower_bound(key), _nil);
  }

  iterator upper_bound(const key_type &key) {
    return iterator(_upper_bound(key), _nil);
  }

  const_iterator upper_bound(const key_type &key) const {
    return const_iterator(_upper_bound(key), _nil);
  }

  ft::pair<iterator, iterator> equal_range(const key_type &key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type &key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  allocator_type get_allocator() const { return allocator_type(_alloc); }

private:
  // Private methods

  const key_type _key(node_ptr node) const {
    return KeyOfValue()(*(node->data));
  }

  const key_type _key(value_type val) const { return KeyOfValue()(val); }

  node_ptr _new_node(const value_type &value,
                     const typename node_type::color_type color = RED) {
    node_ptr z = _node_alloc.allocate(1);
    _node_alloc.construct(z, node_type(value, color, _nil, _alloc));
    return z;
  }

  /* @brief Get the node with the minimum value in the subtree rooted at node.
   * @param node The root of the subtree.
   * @return The node with the minimum value in the subtree rooted at node.
   */
  node_ptr _minimum(node_ptr node) const {
    if (node == _nil)
      return _nil;
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
    if (node == _nil)
      return _nil;
    while (node->right != _nil) {
      node = node->right;
    }
    return node;
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

  node_ptr _lower_bound(const key_type &key) const {
    node_ptr x = _root;
    node_ptr y = _nil;
    while (x != _nil) {
      if (!_comp(_key(x), key))
        y = x, x = x->left;
      else
        x = x->right;
    }
    return y;
  }

  node_ptr _upper_bound(const key_type &key) const {
    node_ptr x = _root;
    node_ptr y = _nil;
    while (x != _nil) {
      if (_comp(key, _key(x)))
        y = x, x = x->left;
      else
        x = x->right;
    }
    return y;
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

  /* @brief Inserts a new node with the given key and mapped value.
   *
   * @param value_type A pair of the key and the mapped value.
   * @return An iterator to the inserted node.
   *
   * Inserts a new node with the given key and value.
   * If the key already exists, the value is not updated.
   * For optimization, the non-existence of the key should be checked
   * on the caller function.
   *
   *
   *     p                           p
   *    / \                         / \
   *   l   q                       l   q
   *      / \   =>                /   / \
   *     p   r                   z   l   q
   *
   */

  ft::pair<iterator, bool> _insert(const value_type &val) {
    node_ptr y = _nil;
    node_ptr x = _root;
    while (x != _nil) {
      y = x;
      if (!_comp(_key(val), _key(x)) && !_comp(_key(x), _key(val))) {
        _nil->aux = _maximum(_root);
        return ft::make_pair(iterator(x, _nil), false);
      } else if (_comp(_key(val), _key(x)))
        x = x->left;
      else
        x = x->right;
    }
    node_ptr z = _new_node(val);
    z->parent = y;
    if (y == _nil)
      _root = z;
    else if (_comp(_key(z), _key(y)))
      y->left = z;
    else
      y->right = z;
    z->left = _nil;
    z->right = _nil;
    z->color = RED;
    _insert_fixup(z);
    ++_size;
    _nil->aux = _maximum(_root);
    return ft::make_pair(iterator(z, _nil), true);
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
      _destroy_node(node);
    }
  }

  void _destroy_node(node_ptr node) {
    _node_alloc.destroy(node);
    _node_alloc.deallocate(node, 1);
  }

  /* @brief Removes the node z from the tree.
   *
   * @param z The node to be removed.
   *
   * At the end of the deletion, the node z is removed from the tree,
   * and the tree is rebalanced, accordingly to the Red Black Tree
   * properties.
   */

  void _erase_aux(iterator position) {
    node_ptr y = _remove(position._node);
    _destroy_node(y);
    --_size;
    _nil->aux = _maximum(_root);
  }

  void _erase_aux(iterator first, iterator last) {
    if (first == begin() && last == end())
      clear();
    else {
      while (first != last) {
        erase(first++);
      }
    }
  }

  node_ptr _remove(node_ptr z) {
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
      if (y->parent == z)
        x->parent = y;
      else {
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
    return z;
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

  node_ptr _tree_rebalance_for_erase(node_ptr const z) {
    node_ptr y = z;
    node_ptr x = 0;
    node_ptr x_parent = 0;

    if (y->left == _nil)
      x = y->right;
    else if (y->right == _nil)
      x = y->left;
    else {
      y = y->right;
      while (y->left != _nil)
        y = y->left;
      x = y->right;
    }
    if (y != z) {
      z->left->parent = y;
      y->left = z->left;
      if (y != z->right) {
        x_parent = y->parent;
        if (x)
          x->parent = y->parent;
        y->parent->left = x;
        y->right = z->right;
        z->right->parent = y;
      } else
        x_parent = y;
      if (_root == z)
        _root = y;
      else if (z->parent->left == z)
        z->parent->left = y;
      else
        z->parent->right = y;
      y->parent = z->parent;
      std::swap(y->color, z->color);
      y = z;
    } else {
      x_parent = y->parent;
      if (x)
        x->parent = y->parent;
      if (_root == z)
        _root = x;
      else if (z->parent->left == z)
        z->parent->left = x;
      else
        z->parent->right = x;
    }
    if (y->color != RED) {
      while (x != _root && (x == _nil || x->color == BLACK))
        if (x == x_parent->left) {
          node_ptr w = x_parent->right;
          if (w->color == RED) {
            w->color = BLACK;
            x_parent->color = RED;
            _left_rotate(x_parent);
            w = x_parent->right;
          }
          if ((w->left == _nil || w->left->color == BLACK) &&
              (w->right == _nil || w->right->color == BLACK)) {
            w->color = RED;
            x = x_parent;
            x_parent = x_parent->parent;
          } else {
            if (w->right == _nil || w->right->color == BLACK) {
              w->left->color = BLACK;
              w->color = RED;
              _right_rotate(w);
              w = x_parent->right;
            }
            w->color = x_parent->color;
            x_parent->color = BLACK;
            if (w->right != _nil)
              w->right->color = BLACK;
            _left_rotate(x_parent);
            break;
          }
        } else {
          node_ptr w = x_parent->left;
          if (w->color == RED) {
            w->color = BLACK;
            x_parent->color = RED;
            _right_rotate(x_parent);
            w = x_parent->left;
          }
          if ((w->right == _nil || w->right->color == BLACK) &&
              (w->left == _nil || w->left->color == BLACK)) {
            w->color = RED;
            x = x_parent;
            x_parent = x_parent->parent;
          } else {
            if (w->left == _nil || w->left->color == BLACK) {
              w->right->color = BLACK;
              w->color = RED;
              _left_rotate(w);
              w = x_parent->left;
            }
            w->color = x_parent->color;
            x_parent->color = BLACK;
            if (w->left != _nil)
              w->left->color = BLACK;
            _right_rotate(x_parent);
            break;
          }
        }
      if (x == _nil)
        x->color = BLACK;
    }
    return y;
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
   * The rotation is performed such that the node x becomes the left child
   * of its right child. The right child is returned as the result of the
   * rotation. The rotation is performed in-place. The color of x is
   * preserved.
   */
  void _left_rotate(node_ptr x) {
    if (x == _nil || x->right == _nil)
      return;
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
   * The rotation is performed such that the node x becomes the right
   * child of its left child. The left child is returned as the result of
   * the rotation. The rotation is performed in-place. The color of x is
   * preserved.
   */
  void _right_rotate(node_ptr x) {
    if (x == _nil || x->left == _nil)
      return;
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

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::RedBlackTree<Key, T, Compare, Alloc> &lhs,
                const ft::RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const RedBlackTree<Key, T, Compare, Alloc> &lhs,
                const RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const RedBlackTree<Key, T, Compare, Alloc> &lhs,
               const RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const RedBlackTree<Key, T, Compare, Alloc> &lhs,
               const RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const RedBlackTree<Key, T, Compare, Alloc> &lhs,
                const RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const RedBlackTree<Key, T, Compare, Alloc> &lhs,
                const RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(RedBlackTree<Key, T, Compare, Alloc> &lhs,
          RedBlackTree<Key, T, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}

} // namespace ft

#endif
