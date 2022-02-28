#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "type_traits.hpp"
#include <memory>
#include <sstream>
#include <stdexcept>

namespace ft {

/**
 * @brief A vector class.
 * @tparam T The type of the elements.
 * @tparam Allocator The allocator type.
 */
template <class T, class Alloc = std::allocator<T>> class vector {
public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::random_access_iterator<value_type> iterator;
  typedef ft::random_access_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef std::size_t size_type;

private:
  value_type *_data;     // pointer to the first element in the vector
  size_type _size;       // number of elements in the vector
  size_type _capacity;   // capacity of the vector
  allocator_type _alloc; // allocator object
  static const size_type _init_capacity = 0; // Initial capacity
  static const size_type _growth_factor = 2; // Growth factor

  /**
   * @brief Check if the vector has enough capacity to store n elements.
   * @param n The number of elements to store.
   */
  void _M_range_check(size_type __n) const {
    if (__n >= size()) {
      std::stringstream ss;
      ss << "vector::_M_range_check: __n (which is " << __n
         << ") >= this->size() (which is " << size() << ")";
      throw std::out_of_range(ss.str());
    }
  }

public:
  // Member functions

  /**
   * @brief Default constructor.
   *
   * Creates an empty vector.
   */
  explicit vector(const allocator_type &alloc = allocator_type())
      : _data(NULL), _size(0), _capacity(_init_capacity), _alloc(alloc) {
    _data = _alloc.allocate(_capacity);
  };

  /**
   * @brief Fill constructor.
   * @param n The number of elements to store.
   * @param val The value to fill the vector with.
   * @param alloc The allocator to use.
   *
   * Creates a vector with n elements, each initialized to val.
   * If alloc is not specified, the default allocator is used.
   */
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    if (n > max_size())
      throw std::length_error("ft::vector::vector(size_type, const "
                              "value_type&, const allocator_type&)");
    _data = _alloc.allocate(_size * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, val);
    }
  }

  /**
   * @brief Range constructor.
   * @param first The first element in the range.
   * @param last The last element in the range.
   * @param alloc The allocator to use.
   *
   * Creates a vector with the elements in the range [first, last).
   * If alloc is not specified, the default allocator is used.
   * If the range is empty, the vector is empty.
   * If the range contains more elements than can be stored in the vector,
   * the behavior is undefined.
   */
  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
             * = 0)
      : _alloc(alloc) {
    _size = ft::distance(first, last);
    _capacity = _size < _init_capacity ? _init_capacity : _size;
    _data = _alloc.allocate(_capacity * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, *(first + i));
    }
  }

  /**
   * @brief Copy constructor.
   * @param x The vector to copy.
   *
   * Creates a vector with the same elements as the given vector.
   */
  vector(const vector &x)
      : _size(x._size), _capacity(x._capacity), _alloc(Alloc(x._alloc)) {
    _data = _alloc.allocate(_capacity * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, x._data[i]);
    }
  }

  /**
   * @brief Default destructor.
   * Deallocates the memory used by the vector.
   *
   * If the vector owns the memory, the destructor deallocates the memory.
   * If the vector does not own the memory, the destructor does nothing.
   * The destructor does not deallocate memory if the vector owns the memory
   * and the vector is empty.
   */
  ~vector() {
    if (_data != NULL) {
      for (size_type i = 0; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
      _alloc.deallocate(_data, _capacity * sizeof(value_type));
    }
  }

  /**
   * @brief Copy assignment operator.
   * @param x The vector to copy.
   *
   * Replaces the contents of the vector with the contents of the given
   * vector.
   */
  vector &operator=(const vector &x) {
    if (this != &x) {
      if (_size != x._size) {
        if (_data != NULL) {
          for (size_type i = 0; i < _size; i++) {
            _alloc.destroy(_data + i);
          }
          _alloc.deallocate(_data, _capacity * sizeof(value_type));
        }
        _size = x._size;
        _capacity = x._capacity;
        _data = _alloc.allocate(_capacity * sizeof(value_type));
      }
      for (size_type i = 0; i < _size; i++) {
        _alloc.construct(_data + i, x._data[i]);
      }
    }
    return *this;
  }

  // Iterators

  /**
   * @brief Returns an iterator to the first element of the container.
   *
   * @return iterator to the first element of the container.
   */
  iterator begin() { return iterator(_data); }

  /**
   * @brief Returns a const_iterator to the first element of the container.
   *
   * @return const_iterator to the first element of the container.
   */
  const_iterator begin() const { return const_iterator(_data); }

  /**
   * @brief Returns an iterator to the last element of the container.
   *
   * @return iterator to the last element of the container.
   */
  iterator end() { return begin() + size(); }

  /**
   * @brief Returns a const_iterator to the last element of the container.
   *
   * @return const_iterator to the last element of the container.
   */
  const_iterator end() const { return begin() + size(); }

  /**
   * @brief Returns a reverse_iterator to the first element of the reversed
   * container.
   *
   * @return reverse_iterator to the first element of the reversed container.
   */
  reverse_iterator rbegin() { return reverse_iterator(end()); }

  /**
   * @brief Returns a const_reverse_iterator to the first element of the
   * reversed container.
   *
   * @return const_reverse_iterator to the first element of the reversed
   * container.
   */
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  /**
   * @brief Returns a reverse_iterator to the last element of the reversed
   * container.
   *
   * @return reverse_iterator to the last element of the reversed container.
   */
  reverse_iterator rend() { return reverse_iterator(begin()); }

  /**
   * @brief Returns a const_reverse_iterator to the last element of the
   * reversed container.
   *
   * @return const_reverse_iterator to the last element of the reversed
   * container.
   */
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Capacity

  /**
   * @brief Returns the number of elements in the container.
   *
   * @return the number of elements in the container.
   */
  size_type size() const { return _size; }

  /**
   * @brief Returns the maximum number of elements the container can hold.
   *
   * @return the maximum number of elements the container can hold.
   */
  size_type max_size() const { return _alloc.max_size(); }

  /**
   * @brief Resize the container so that it contains n elements.
   *
   * @param n New container size, expressed in number of elements.
   * @param val Value to fill the new elements with. If not specified, the
   * default constructor is used.
   *
   * @return none
   */
  void resize(size_type n, value_type val = value_type()) {
    if (n > _size) {
      reserve(n);
      for (size_type i = _size; i < n; i++) {
        _alloc.construct(_data + i, val);
      }
    } else if (n < _size) {
      for (size_type i = n; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
    }
    _size = n;
  }

  /**
   * @brief Returns the size of the storage space currently allocated for the
   * vector, expressed in terms of elements.
   *
   * @return the size of the storage space currently allocated for the vector,
   * expressed in terms of elements.
   */
  size_type capacity() const { return _capacity; }

  /**
   * @brief Checks if the container has no elements.
   *
   * @return true if the container has no elements, false otherwise.
   */
  bool empty() const { return size() == 0; }

  /**
   * @brief Changes the capacity of the vector to the specified value.
   *
   * @param n New capacity, expressed in terms of elements.
   *
   * @return none
   *
   * If n is greater than the current capacity, the function causes the
   * container to reallocate its storage increasing its capacity to n (or
   * greater). In all other cases, the container makes no allocation or
   * deallocation.
   */
  void reserve(size_type n) {
    if (n > max_size()) {
      throw std::length_error("ft::vector::reserve");
    }
    if (n > _capacity) {
      _capacity = n;
      pointer tmp = _alloc.allocate(_capacity * sizeof(value_type));
      for (size_type i = 0; i < _size; i++) {
        _alloc.construct(tmp + i, _data[i]);
      }
      for (size_type i = 0; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
      _alloc.deallocate(_data, _size * sizeof(value_type));
      _data = tmp;
    }
  }

  // Element access

  /**
   * @brief Returns a reference to the element at position n in the container.
   *
   * @param n Position of the element to return.
   *
   * @return A reference to the element at position n in the container.
   */
  reference operator[](size_type n) { return *(begin() + n); }

  /**
   * @brief Returns a const reference to the element at position n in the
   * container.
   *
   * @param n Position of the element to return.
   *
   * @return A const reference to the element at position n in the container.
   */
  const_reference operator[](size_type n) const { return *(begin() + n); }

  /**
   * @brief Returns a reference to the element at position n in the container.
   *
   * @param n Position of the element to return.
   * @return A reference to the element at position n in the container.
   * @throws std::out_of_range if n is out of range.
   */
  reference at(size_type n) {
    _M_range_check(n);
    return *(begin() + n);
  }

  /**
   * @brief Returns a const reference to the element at position n in the
   * container.
   *
   * @param n Position of the element to return.
   * @return A const reference to the element at position n in the container.
   * @throws std::out_of_range if n is out of range.
   */
  const_reference at(size_type n) const {
    _M_range_check(n);
    return *(begin() + n);
  }

  /**
   * @brief Returns a reference to the first element in the container.
   *
   * @return A reference to the first element in the container.
   */
  reference front() { return *begin(); }

  /**
   * @brief Returns a const reference to the first element in the container.
   *
   * @return A const reference to the first element in the container.
   */
  const_reference front() const { return *begin(); }

  /**
   * @brief Returns a reference to the last element in the container.
   *
   * @return A reference to the last element in the container.
   */
  reference back() { return *(end() - 1); }

  /**
   * @brief Returns a const reference to the last element in the container.
   *
   * @return A const reference to the last element in the container.
   */
  const_reference back() const { return *(end() - 1); }

  // Modifiers

  /**
   * @brief Assigns new contents to the container, replacing its current
   * contents, and modifying its size accordingly. The new contents are
   * constructed in the same order as the original contents.
   *
   * @param first The iterator to the first element in the range of elements
   * to be copied.
   * @param last The iterator to the one past the last element in the range of
   * elements to be copied.
   *
   * @return none
   */
  template <class InputIterator>
  void assign(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    size_type n = ft::distance(first, last);
    if (n > max_size()) {
      throw std::length_error("ft::vector::assign");
    }
    if (n > capacity()) {
      reserve(n);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + i, *(first + i));
    }
    for (size_type i = n; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _size = n;
  }

  /**
   * @brief Assigns new contents to the container, replacing its current
   * contents, and modifying its size accordingly.
   *
   * @param n New size of the container, expressed in terms of elements.
   * @param val Value to fill the new elements with. If not specified, the
   * default constructor is used.
   *
   * @return none
   */
  void assign(size_type n, const value_type &val) {
    if (n > max_size()) {
      throw std::length_error("ft::vector::assign");
    }
    if (n > capacity()) {
      reserve(n);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(&(*(begin() + i)), val);
    }
    for (size_type i = n; i < _size; i++) {
      _alloc.destroy(&(*(begin() + i)));
    }
    _size = n;
  }

  /**
   * @brief Inserts a new element at the last position in the container.
   *
   * @param val Value to be inserted as a new element.
   * @return none
   * @throws std::length_error if the container is full.
   * @throws std::bad_alloc if the allocation of the new element fails.
   */
  void push_back(const value_type &val) {
    if (_size == capacity()) {
      reserve(capacity() ? capacity() * _growth_factor : 1);
    }
    _alloc.construct(&(*(begin() + size())), val);
    _size++;
  };

  /**
   * @brief Removes the last element in the container.
   *
   * @return none
   * @throws std::out_of_range if the container is empty.
   */
  void pop_back() {
    if (_size > 0) {
      _alloc.destroy(_data + _size - 1);
      _size--;
    } else {
      throw std::out_of_range("ft::vector::pop_back");
    }
  };

  /**
   * @brief Inserts a new element at the specified position.
   *
   * @param position Position to insert the new element.
   * @param val Value to fill the new element with. If not specified, the
   * default constructor is used.
   *
   * @return iterator to the newly inserted element.
   */
  iterator insert(iterator position, const value_type &val) {
    size_type _offset = position - begin();
    if (_size == capacity()) {
      reserve(capacity() * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(&(*begin()) + i, *(begin() + i - 1));
    }
    _alloc.construct(&(*begin()) + _offset, val);
    _size++;
    return iterator(begin() + _offset);
  }

  /**
   * @brief Inserts n copies of val at position position.
   *
   * @param position Position to insert the new elements.
   * @param n Number of elements to insert.
   * @param val Value to fill the new elements with. If not specified, the
   * default constructor is used.
   * @return none
   */
  void insert(iterator position, size_type n, const value_type &val) {
    size_type _offset = position - begin();
    if (_size + n > capacity()) {
      reserve(capacity() * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(&(*begin()) + i + n - 1, *(begin() + i - 1));
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(&(*begin()) + _offset + i, val);
    }
    _size += n;
  }

  /**
   * @brief Inserts a range of elements at the specified position.
   *
   * @param position Position to insert the new elements.
   * @param first The iterator to the first element in the range of elements
   * to be inserted.
   * @param last The iterator to the one past the last element in the range of
   * elements to be inserted.
   *
   * @return none
   */
  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    size_type _offset = position - begin();
    size_type n = ft::distance(first, last);
    if (_size + n > _capacity) {
      reserve(capacity() * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(&(*begin()) + i + n - 1, *(begin() + i - 1));
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(&(*begin()) + _offset + i, *(first + i));
    }
    _size += n;
  };

  /**
   * @brief Removes the element at the specified position.
   *
   * @param position Position of the element to be removed.
   *
   * @return none
   *
   * @throws std::out_of_range if the container is empty.
   * @throws std::out_of_range if the position is out of range.
   */
  iterator erase(iterator position) {
    if (size() == 0 || position >= end() || position < begin()) {
      throw std::out_of_range("ft::vector::erase");
    }
    for (size_type i = position - _data; i < _size - 1; i++) {
      _alloc.construct(_data + i, _data[i + 1]);
    }
    _alloc.destroy(_data + _size - 1);
    _size--;
    return position;
  };

  /**
   * @brief Removes the elements in the range [first, last).
   *
   * @param first The iterator to the first element in the range of elements
   * to be removed.
   * @param last The iterator to the one past the last element in the range of
   * elements to be removed.
   *
   * @return none
   * @throws std::out_of_range if the container is empty.
   * @throws std::out_of_range if the position is out of range.
   */
  iterator erase(iterator first, iterator last) {
    if (size() == 0 || first >= end() || last < begin()) {
      throw std::out_of_range("ft::vector::erase");
    }
    for (iterator it = first; it != last; it++) {
      _alloc.destroy(&(*it));
    }
    for (iterator it = last; it != end(); it++) {
      _alloc.construct(&(*(it - (last - first))), *it);
    }
    _size -= last - first;
    return first;
  };

  /**
   * @brief Swaps the contents of the container with those of other.
   * @param other The container to swap with.
   * @return none
   */
  void swap(vector &x) {
    ft::swap(_data, x._data);
    ft::swap(_size, x._size);
    ft::swap(_capacity, x._capacity);
  };

  /**
   * @brief Clears the contents of the container. After this call, size()
   * returns zero. Does not deallocate memory.
   * @return none
   */
  void clear() {
    for (iterator it = begin(); it != end(); ++it) {
      _alloc.destroy(&(*it));
    }
    _size = 0;
  };

  // Allocator

  /**
   * @brief Returns the allocator object associated with the container.
   * @return The allocator object associated with the container.
   */
  allocator_type get_allocator() const { return _alloc; }
};

// Non-member functions

/**
 * @brief Compares two vectors for equality.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the two vectors are equal, false otherwise.
 */
template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * @brief Compares two vectors for inequality.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the two vectors are not equal, false otherwise.
 */
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

/**
 * @brief Compares two vectors for less than.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the first vector is less than the second, false otherwise.
 */
template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

/**
 * @brief Compares two vectors for greater than.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the first vector is greater than the second, false
 * otherwise.
 */
template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return rhs < lhs;
}

/**
 * @brief Compares two vectors for less than or equal to.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the first vector is less than or equal to the second, false
 * otherwise.
 */
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(rhs < lhs);
}

/**
 * @brief Compares two vectors for greater than or equal to.
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return true if the first vector is greater than or equal to the second,
 * false otherwise.
 */
template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

/*
 * @brief Swaps the contents of two vectors. Equivalent to lhs.swap(rhs).
 * @param lhs The first vector.
 * @param rhs The second vector.
 * @return none
 */
template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

} // namespace ft

#endif
