#ifndef MAP_HPP
#define MAP_HPP

#include "algorithm.hpp"
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

  class value_compare : ft::binary_function<value_type, value_type, bool> {
    friend class map<Key, T, Compare, Alloc>;

  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

private:
  typedef RedBlackTree<Key, T, Compare, Alloc> _tree_type;
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
  typedef typename iterator_traits<iterator>::difference_type difference_type;

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

  // Element Access

  /**
   * @brief Returns a reference to the element with the specified key.
   *
   * @param key The key of the element to return.
   *
   * @return A reference to the element with the specified key.
   */
  mapped_type &operator[](const key_type &k) {
    return (*((insert(make_pair(k, mapped_type()))).first)).second;
  }

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
    return _tree.insert_unique(val);
  }

  /**
   * @brief Insert with hint
   * @param hint The position where the new element will be inserted.
   * @param val The value to be inserted, as a pair of key and mapped value.
   * @return An iterator to the inserted element.
   */
  iterator insert(iterator hint, const value_type &val) {
    return _tree.insert_unique(hint, val);
  }

  /**
   * @brief Insert multiple elements
   *
   * @param first The iterator to the first element in the range.
   * @param last The iterator to the last element in the range.
   * @return An iterator to the element after the last inserted element.
   */
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _tree.insert_unique(first, last);
  }

  /**
   * @brief Erase an element by iterator
   *
   * @param pos The position of the element to be erased.
   * @return An iterator to the element after the erased element.
   */

  void erase(iterator pos) { return _tree.erase(pos); }

  /**
   * @brief Erase an element by key
   *
   * @param key The key of the element to be erased.
   * @return The number of elements erased.
   */
  size_type erase(const key_type &key) { return _tree.erase(key); }

  /**
   * @brief Erase a range of elements
   *
   * @param first The iterator to the first element in the range.
   * @param last The iterator to the last element in the range.
   * @return An iterator to the element after the last erased element.
   */

  void erase(iterator first, iterator last) { return _tree.erase(first, last); }

  /**
   * @brief Swap the contents of the container with those of another.
   *
   * @param x The other map.
   * @return void
   */
  void swap(map &x) { _tree.swap(x._tree); }

  /**
   * @brief Clear the container
   *
   * The clear() function removes all elements from the container (which
   * effectively reduces the container to its default state). The container
   * will be empty after this call returns.
   */
  void clear() { _tree.clear(); }

  // Observers

  /**
   * @brief Returns the comparison object.
   *
   * @return The comparison object.
   */
  key_compare key_comp() const { return _tree.key_comp(); }

  /**
   * @brief Returns the comparison object.
   *
   * @return The comparison object.
   */

  value_compare value_comp() const { return value_compare(key_comp()); }

  // Operations

  /**
   * @brief Find element
   *
   * @param key The key of the element to be found.
   * @return An iterator to the element, or end() if the element is not found.
   */

  iterator find(const key_type &key) { return _tree.find(key); }

  const_iterator find(const key_type &key) const { return _tree.find(key); }

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
  iterator lower_bound(const key_type &k) { return _tree.lower_bound(k); }

  const_iterator lower_bound(const key_type &k) const {
    return _tree.lower_bound(k);
  }

  /**
   * @brief Return iterator to upper bound
   *
   * @param key The key of the element to be found.
   * @return An iterator pointing to the first element that whose key
   * is considered to go after key. If no such element is found, end() is
   * returned.
   */

  iterator upper_bound(const key_type &k) { return _tree.upper_bound(k); }

  const_iterator upper_bound(const key_type &k) const {
    return _tree.upper_bound(k);
  }

  /**
   * @brief Return range of equal elements
   *
   * @param key The key of the element to be found.
   * @return A pair of iterators that delimit a range of elements with key
   * equivalent to key. If no such element is found, the range returned has
   * first == last.
   */
  ft::pair<iterator, iterator> equal_range(const key_type &k) {
    return _tree.equal_range(k);
  }

  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type &k) const {
    return _tree.equal_range(k);
  }

  // Allocator

  /**
   * @brief Returns the allocator object.
   *
   * @return The allocator object.
   */
  allocator_type get_allocator() const { return _tree.get_allocator(); }
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                const ft::map<Key, T, Compare, Alloc> &rhs) {
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}

} // namespace ft

#endif
