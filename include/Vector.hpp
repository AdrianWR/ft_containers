#pragma once

#include "iterator_traits.hpp"
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "nullptr.hpp"
#include <iterator>

namespace Vector {

template <typename T>
class iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;

private:
  T *_ptr;

public:
  iterator() : _ptr(ft::u_nullptr) {}

  iterator(T *ptr) : _ptr(ptr) {}

  iterator(const iterator &i) : _ptr(i.ptr) {}

  iterator &operator=(const iterator &i) {
    if (this != &i)
      _ptr = i.ptr;
    return *this;
  }

  ~iterator() {}

  bool operator==(const iterator &i) const { return _ptr == i._ptr; }

  bool operator!=(const iterator &i) const { return _ptr != i._ptr; }

  T &operator*() const { return *_ptr; }

  T *operator->() const { return _ptr; }

  iterator &operator++() {
    ++_ptr;
    return *this;
  }

  iterator operator++(int) {
    iterator tmp(*this);
    ++_ptr;
    return tmp;
  }

  iterator &operator--() {
    --_ptr;
    return *this;
  }

  iterator operator--(int) {
    iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  iterator operator+(int n) const {
    iterator tmp(*this);
    tmp._ptr += n;
    return tmp;
  }

  iterator operator-(int n) const {
    iterator tmp(*this);
    tmp._ptr -= n;
    return tmp;
  }

  bool operator<(const iterator &i) const { return _ptr < i._ptr; }

  bool operator>(const iterator &i) const { return _ptr > i._ptr; }

  bool operator<=(const iterator &i) const { return _ptr <= i._ptr; }

  bool operator>=(const iterator &i) const { return _ptr >= i._ptr; }

  int operator-(const iterator &i) const { return _ptr - i._ptr; }

  iterator &operator+=(int n) {
    _ptr += n;
    return *this;
  }

  iterator &operator-=(int n) {
    _ptr -= n;
    return *this;
  }

  T &operator[](int n) const { return _ptr[n]; }
};

} // namespace Vector

namespace ft {

template <class T, class Alloc = std::allocator<T>> class vector {
public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef Vector::iterator<value_type> iterator;
  typedef Vector::iterator<const value_type> const_iterator;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef std::size_t size_type;

private:
  value_type *_data;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;

public:
  // Member functions

  explicit vector(const allocator_type &alloc = allocator_type())
      : _data(NULL), _size(0), _capacity(0), _alloc(alloc){};

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    _data = _alloc.allocate(n * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, val);
    }
  }

  vector(const vector &v) {
    _data = Alloc::allocate(_size);
    for (unsigned int i = 0; i < _size; i++) {
      _data[i] = v[i];
    }
  };

  vector &operator=(const vector &v) {
    if (this != &v) {
      _data = Alloc::allocate(_size);
      for (unsigned int i = 0; i < _size; i++) {
        _data[i] = v[i];
      }
    }
  };

  ~vector() {
    if (_data != u_nullptr) {
      for (unsigned int i = 0; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
      _alloc.deallocate(_data, _size);
    }
  };

  // Capacity

  bool empty() const { return _size == 0; }

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

  void reserve(size_type n) {
    if (n > _capacity) {
      value_type *tmp = _alloc.allocate(n * sizeof(value_type));
      for (size_type i = 0; i < _size; i++) {
        _alloc.construct(tmp + i, _data[i]);
      }
      _alloc.deallocate(_data, _capacity);
      _data = tmp;
      _capacity = n;
    }
  };

  size_type capacity() const { return _capacity; }

  void resize(size_type n, value_type val = value_type()) {
    if (n > _capacity) {
      reserve(n << 1);
    }
    for (size_type i = _size; i < n; i++) {
      _alloc.construct(_data + i, val);
    }
    _size = n;
  };

  // Modifiers

  void clear() {
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _size = 0;
  };

  iterator insert(iterator pos, const value_type &val) {
    if (_size == _capacity) {
      reserve(_capacity << 1);
    }
    for (size_type i = _size; i > pos - _data; i--) {
      _alloc.construct(_data + i, _data[i - 1]);
      _alloc.destroy(_data + i - 1);
    }
    _alloc.construct(_data + pos - _data, val);
    _size++;
    return pos;
  };

  iterator begin() { return iterator(_data); }

  iterator end() { return iterator(_data + _size); }
};

} // namespace ft

#endif
