#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "type_traits.hpp"
#include <algorithm>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <iostream>

namespace ft {

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

  // Member functions

  explicit vector(const allocator_type &alloc = allocator_type())
      : _data(NULL), _size(0), _capacity(_init_capacity), _alloc(alloc) {
    _data = _alloc.allocate(_capacity);
  };

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    _data = _alloc.allocate(_size * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, val);
    }
  }

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

  vector(const vector &x)
      : _size(x._size), _capacity(x._capacity), _alloc(Alloc(x._alloc)) {
    _data = _alloc.allocate(_capacity * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, x._data[i]);
    }
  }

  ~vector() {
    if (_data != NULL) {
      for (size_type i = 0; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
      _alloc.deallocate(_data, _capacity * sizeof(value_type));
    }
  }

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

  iterator begin() { return iterator(_data); }

  const_iterator begin() const { return const_iterator(_data); }

  iterator end() { return iterator(_data + _size); }

  const_iterator end() const { return const_iterator(_data + _size); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Capacity

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

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

  size_type capacity() const { return _capacity; }

  bool empty() const { return _size == 0; }

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

  reference operator[](size_type n) { return _data[n]; }

  const_reference operator[](size_type n) const { return _data[n]; }

  void _M_range_check(size_type __n) const {
    if (__n >= size()) {
      std::stringstream ss;
      ss << "vector::_M_range_check: __n (which is " << __n
         << ") >= this->size() (which is " << size() << ")";
      throw std::out_of_range(ss.str());
    }
  }

  reference at(size_type n) {
    _M_range_check(n);
    return (*this)[n];
  }

  const_reference at(size_type n) const {
    _M_range_check(n);
    return (*this)[n];
  }

  reference front() { return *begin(); }

  const_reference front() const { return *begin(); }

  reference back() { return *(end() - 1); }

  const_reference back() const { return *(end() - 1); }

  // Modifiers

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

  void assign(size_type n, const value_type &val) {
    if (n > max_size()) {
      throw std::length_error("ft::vector::assign");
    }
    if (n > capacity()) {
      reserve(n);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + i, val);
    }
    for (size_type i = n; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _size = n;
  }

  void push_back(const value_type &val) {
    if (_size == _capacity) {
      reserve(_capacity ? _capacity * _growth_factor : 1);
    }
    _alloc.construct(_data + _size, val);
    _size++;
  };

  void pop_back() {
    if (_size > 0) {
      _alloc.destroy(_data + _size - 1);
      _size--;
    } else {
      throw std::out_of_range("ft::vector::pop_back");
    }
  };

  iterator insert(iterator position, const value_type &val) {
    size_type _offset = position - begin();
    if (_size == _capacity) {
      reserve(_capacity * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(_data + i, _data[i - 1]);
    }
    _alloc.construct(_data + _offset, val);
    _size++;
    return iterator(_data + _offset);
  }

  void insert(iterator position, size_type n, const value_type &val) {
    size_type _offset = position - begin();
    if (_size + n > _capacity) {
      reserve(_capacity * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(_data + i + n - 1, _data[i - 1]);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + _offset + i, val);
    }
    _size += n;
  }

  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    size_type _offset = position - begin();
    size_type n = ft::distance(first, last);
    if (_size + n > _capacity) {
      reserve(_capacity * _growth_factor);
    }
    for (size_type i = _size; i > _offset; i--) {
      _alloc.construct(_data + i + n - 1, _data[i - 1]);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + _offset + i, *(first + i));
    }
    _size += n;
  };

  iterator erase(iterator position) {
    for (size_type i = position - _data; i < _size - 1; i++) {
      _alloc.construct(_data + i, _data[i + 1]);
    }
    _alloc.destroy(_data + _size - 1);
    _size--;
    return position;
  };

  iterator erase(iterator first, iterator last) {
    for (size_type i = first - _data; i < last - _data; i++) {
      _alloc.destroy(_data + i);
    }
    for (size_type i = first - _data; i < _size - (last - first); i++) {
      _alloc.construct(_data + i, _data[i + (last - first)]);
    }
    _size -= last - first;
    return first;
  };

  void swap(vector &x) {
    ft::swap(_data, x._data);
    ft::swap(_size, x._size);
    ft::swap(_capacity, x._capacity);
  };

  void clear() {
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _size = 0;
  };

  // Allocator

  allocator_type get_allocator() const { return _alloc; }

private:
  value_type *_data;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
  static const size_type _init_capacity = 0;
  static const size_type _growth_factor = 2;
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

} // namespace ft

#endif
