#ifndef SET_HPP
#define SET_HPP

#include "functional.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include <memory>

namespace ft {

template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T>>
class set {
public:
  typedef T value_type;
  typedef T key_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;

private:
  typedef RedBlackTree<T, T, _Identity<T>, Compare, Alloc> _tree_type;

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

  // Constructors

  /**
   * @brief Constructs an empty set.
   */
  explicit set(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc) {}

  /**
   * @brief Constructs a set with the elements in the range [first, last).
   */
  template <class InputIterator>
  set(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc) {
    _tree.insert_unique(first, last);
  }

  /**
   * @brief Copy constructor.
   */
  set(const set &x) : _tree(x._tree) {}

  /**
   * @brief Default destructor.
   */
  ~set() {}

  /**
   * @brief Copy assignment operator.
   */
  set &operator=(const set &x) {
    _tree = x._tree;
    return *this;
  }

  // Iterators

  /**
   * @brief Returns an iterator to the first element in the container.
   */
  iterator begin() { return _tree.begin(); }

  /**
   * @brief Returns a const_iterator to the first element in the container.
   */
  const_iterator begin() const { return _tree.begin(); }

  /**
   * @brief Returns an iterator to the element following the last element in
   * the container.
   */
  iterator end() { return _tree.end(); }

  /**
   * @brief Returns a const_iterator to the element following the last element
   * in the container.
   */
  const_iterator end() const { return _tree.end(); }

  /**
   * @brief Returns a reverse_iterator to the first element in the reversed
   * container.
   */
  reverse_iterator rbegin() { return _tree.rbegin(); }

  /**
   * @brief Returns a const_reverse_iterator to the first element in the
   * reversed container.
   */
  const_reverse_iterator rbegin() const { return _tree.rbegin(); }

  /**
   * @brief Returns a reverse_iterator to the element following the last
   * element in the reversed container.
   */
  reverse_iterator rend() { return _tree.rend(); }

  /**
   * @brief Returns a const_reverse_iterator to the element following the last
   * element in the reversed container.
   */
  const_reverse_iterator rend() const { return _tree.rend(); }

  // Capacity

  /**
   * @brief Returns true if the container is empty.
   */
  bool empty() const { return _tree.empty(); }

  /**
   * @brief Returns the number of elements in the container.
   */
  size_type size() const { return _tree.size(); }

  /**
   * @brief Returns the maximum number of elements the container can hold.
   */
  size_type max_size() const { return _tree.max_size(); }

  // Modifiers

  /**
   * @brief Inserts a value into the container.
   */
  ft::pair<iterator, bool> insert(const value_type &val) {
    return _tree.insert_unique(val);
  }

  /**
   * @brief Inserts a value into the container.
   */
  iterator insert(iterator hint, const value_type &val) {
    return _tree.insert_unique(hint, val);
  }

  /**
   * @brief Inserts a range of values into the container.
   */
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _tree.insert_unique(first, last);
  }

  /**
   * @brief Removes an element from the container.
   */
  void erase(iterator pos) { _tree.erase(pos); }

  /**
   * @brief Removes an element from the container.
   */
  size_type erase(const key_type &key) { return _tree.erase(key); }

  /**
   * @brief Removes a range of elements from the container.
   */
  void erase(iterator first, iterator last) { _tree.erase(first, last); }

  /**
   * @brief Swap the contents of the container with those of x.
   */
  void swap(set &x) { _tree.swap(x._tree); }

  /**
   * @brief Removes all elements from the container.
   */
  void clear() { _tree.clear(); }

  // Observers

  /**
   * @brief Returns the comparison object.
   */
  key_compare key_comp() const { return _tree.key_comp(); }

  /**
   * @brief Returns the comparison object.
   */
  value_compare value_comp() const { return _tree.key_comp(); }

  // Operations

  /**
   * @brief Finds an element in the container.
   */
  iterator find(const value_type &val) { return _tree.find(val); }

  const_iterator find(const value_type &val) const { return _tree.find(val); }

  /**
   * @brief Counts the number of elements with the given val.
   */
  size_type count(const value_type &val) const { return _tree.count(val); }

  /**
   * @brief Finds the lower bound of the given key.
   */
  iterator lower_bound(const value_type &val) { return _tree.lower_bound(val); }

  const_iterator lower_bound(const value_type &val) const {
    return _tree.lower_bound(val);
  }

  /**
   * @brief Finds the upper bound of the given key.
   */
  iterator upper_bound(const value_type &val) { return _tree.upper_bound(val); }

  const_iterator upper_bound(const value_type &val) const {
    return _tree.upper_bound(val);
  }

  /**
   * @brief Finds the range of elements with the given key.
   */
  ft::pair<iterator, iterator> equal_range(const value_type &val) {
    return _tree.equal_range(val);
  }

  ft::pair<const_iterator, const_iterator>
  equal_range(const value_type &val) const {
    return _tree.equal_range(val);
  }

  // Allocator

  /**
   * @brief Returns the allocator object.
   */
  allocator_type get_allocator() const { return _tree.get_allocator(); }
};

// Non-member function overloads

template <class Key, class Compare, class Alloc>
bool operator==(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs) {
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class Compare, class Alloc>
bool operator!=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const set<Key, Compare, Alloc> &lhs,
               const set<Key, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end(), Compare());
}

template <class Key, class Compare, class Alloc>
bool operator<=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>(const set<Key, Compare, Alloc> &lhs,
               const set<Key, Compare, Alloc> &rhs) {
  return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator>=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class Key, class Compare, class Alloc>
void swap(set<Key, Compare, Alloc> &lhs, set<Key, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}

} // namespace ft

#endif
