#ifndef MAP_HPP
#define MAP_HPP

#include "functional.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include "utility.hpp"
#include <cstddef>
#include <memory>

namespace ft {

/**
 * @brief A map is a container that stores elements in key-value pairs, and
 * the elements are ordered by their keys. The container supports both unique
 * and non-unique keys. The map is also called associative array or
 * dictionary.
 *
 * @tparam Key The type of the keys.
 * @tparam T The type of the mapped values.
 * @tparam Compare The comparison function object type.
 * @tparam Allocator The allocator type.
 */
template <class Key, class T, class Compare = ft::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T>>>
class map {

public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const Key, T> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;

private:
  typedef ft::RedBlackTree<Key, T, Compare, Alloc> _tree_type;
  typedef typename _tree_type::node_type _node_type;

public:
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename _tree_type::iterator iterator;
  typedef typename _tree_type::const_iterator const_iterator;
  typedef typename _tree_type::reverse_iterator reverse_iterator;
  typedef typename _tree_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _tree_type::size_type size_type;
  typedef typename _tree_type::difference_type difference_type;

private:
  _tree_type _tree;

public:
  // Member Functions

  /**
   * @brief Empty Container Constructor (Default Constructor)
   *
   * @param comp The comparison function object.
   * @param alloc The allocator object.
   *
   * Constructs an empty container, with no elements.
   */
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc){};

  /**
   * @brief Range Constructor
   *
   * @param first The iterator to the first element in the range.
   * @param last The iterator to the last element in the range.
   * @param comp The comparison function object.
   * @param alloc The allocator object.
   *
   * Constructs a container with as many elements as the range [first,last),
   * with each element constructed from its corresponding element in that range.
   */
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc) {
    _tree.insert_unique(first, last);
  };

  /**
   * @brief Copy Constructor
   *
   * @param x The other map.
   *
   * Constructs a container with a copy of each of the elements in x.
   * The copy constructor creates a container that keeps and uses copies of
   * x's allocator and comparison object.
   */
  map(const map &x) : _tree(x._tree) {}

  /**
   * @brief Destructor
   *
   * The destructor destroys the container object. All of the elements in the
   * container are destroyed and all memory is deallocated.
   */
  ~map() {}

  /**
   * @brief Copy Assignment Operator
   *
   * @param x The other map.
   *
   * The assignment operator assigns the contents of x to this map.
   * The current contents of this map are cleared before the copy
   * assignment is performed.
   */
  map &operator=(const map &x) {
    if (this != &x) {
      _tree = x._tree;
    }
    return *this;
  }

  // Iterators

  iterator begin() { return _tree.begin(); }

  const_iterator begin() const { return _tree.begin(); }

  iterator end() { return _tree.end(); }

  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return _tree.rbegin(); }

  const_reverse_iterator rbegin() const { return _tree.rbegin(); }

  reverse_iterator rend() { return _tree.rend(); }

  const_reverse_iterator rend() const { return _tree.rend(); }

  // Capacity

  /**
   * @brief Checks if the container is empty.
   *
   * @return True if the container is empty, false otherwise.
   */
  bool empty() const { return _tree.empty(); }

  /**
   * @brief Returns the number of elements in the container.
   *
   * @return The number of elements in the container.
   */
  size_type size() const { return _tree.size(); }

  /**
   * @brief Returns the maximum number of elements the container can hold.
   *
   * @return The maximum number of elements the container can hold.
   */
  size_type max_size() const { return _tree.max_size(); }

  // Modifiers

  /**
   * @brief Insert single element
   *
   * @param val The value to be inserted, as a pair of key and mapped value.
   * @return A pair of an iterator to the inserted element (or to the
   * element that prevented the insertion) and a bool denoting whether the
   * insertion took place (true) or not (false).
   */
  ft::pair<iterator, bool> insert(const value_type &val) {
    for (iterator it = begin(); it != end(); it++) {
      if (!key_compare(it->first, val.first)) {
        if (!key_compare(val.first, it->first)) {
          return ft::pair<iterator, bool>(it, false);
        } else {
          return ft::pair<iterator, bool>(_tree.insert_unique(val), true);
        }
      }
    }
  }

  /**
   * @brief Insert with hint
   * @param hint The position where the new element will be inserted.
   * @param val The value to be inserted, as a pair of key and mapped value.
   * @return An iterator to the inserted element.
   */
  iterator insert(iterator hint, const value_type &val) {
    if (key_compare(hint->first, val.first)) {
      return _tree.insert_unique(hint, val);
    } else {
      return _tree.insert_unique(val);
    }
  }

  /**
   * @brief Insert multiple elements
   *
   * @param first The iterator to the first element in the range.
   * @param last The iterator to the last element in the range.
   * @return An iterator to the element after the last inserted element.
   */
  template <class InputIterator>
  ft::pair<iterator, bool> insert(InputIterator first, InputIterator last) {}

  // Operations

  /**
   * @brief Find element
   *
   * @param key The key of the element to be found.
   * @return An iterator to the element, or end() if the element is not found.
   */

  iterator find(const key_type &key) {
    for (iterator it = begin(); it != end(); it++) {
      if (!(key_compare(key, it->first) || key_compare(it->first, key))) {
        return it;
      }
    }
    return end();
  }

  const_iterator find(const key_type &key) const {
    for (const_iterator it = begin(); it != end(); it++) {
      if (!(key_compare(key, it->first) || key_compare(it->first, key))) {
        return it;
      }
    }
    return end();
  }

  /**
   * @brief Count elements with a specific key
   *
   * @param key The key of the elements to be counted.
   * @return The number of elements with the specified key.
   *
   * The count operation determines the number of elements in the container
   * that have a key equivalent to key. This operation requires logarithmic
   * time complexity. As all elements in the container are unique, the count
   * operation can only return 1, if an element with the specified key is
   * found, and 0 otherwise.
   */
  size_type count(const key_type &key) const {
    return _tree.find(key) != end() ? 1 : 0;
  }

  /**
   * @brief Return iterator to lower bound
   *
   * @param key The key of the element to be found.
   * @return An iterator to the first element that has a key equivalent to
   * key or goes after. If no such element is found, end() is returned.
   */
  iterator lower_bound(const key_type &k) {
    for (iterator it = begin(); it != end(); ++it) {
      if (!key_compare(k, it->first)) {
        return it;
      }
    }
    return end();
  }

  const_iterator lower_bound(const key_type &k) const {
    for (const_iterator it = begin(); it != end(); ++it) {
      if (!key_compare(k, it->first)) {
        return it;
      }
    }
    return end();
  }

  /**
   * @brief Return iterator to upper bound
   *
   * @param key The key of the element to be found.
   * @return An iterator pointing to the first element that whose key
   * is considered to go after key. If no such element is found, end() is
   * returned.
   */

  iterator upper_bound(const key_type &k) {
    for (iterator it = begin(); it != end(); ++it) {
      if (key_compare(k, it->first)) {
        return it;
      }
    }
    return end();
  }

  const_iterator upper_bound(const key_type &k) const {
    for (const_iterator it = begin(); it != end(); ++it) {
      if (key_compare(k, it->first)) {
        return it;
      }
    }
    return end();
  }
};

} // namespace ft

#endif
