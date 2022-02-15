#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>

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
      : _data(NULL), _size(0), _capacity(0), _alloc(alloc){};

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    _data = _alloc.allocate(n * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, val);
    }
  }

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type())
      : _alloc(alloc) {
    _size = 0;
    _capacity = 0;
    _data = NULL;
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  vector(const vector &v) {
    _data = Alloc::allocate(_size);
    for (unsigned int i = 0; i < _size; i++) {
      _data[i] = v[i];
    }
  };

  ~vector() {
    if (_data != NULL) {
      for (unsigned int i = 0; i < _size; i++) {
        _alloc.destroy(_data + i);
      }
      _alloc.deallocate(_data, _size);
    }
  };

  vector &operator=(const vector &v) {
    if (this != &v) {
      if (_data != NULL) {
        for (size_type i = 0; i < _size; i++) {
          _alloc.destroy(_data + i);
        }
        _alloc.deallocate(_data, _size);
      }
      _size = v._size;
      _capacity = v._capacity;
      _alloc = v._alloc;
      _data = _alloc.allocate(_size);
      for (size_type i = 0; i < _size; i++) {
        _data[i] = v[i];
      }
    }
    return *this;
  };

  // Iterators

  iterator begin() { return iterator(_data); };

  const_iterator begin() const { return const_iterator(_data); };

  iterator end() { return iterator(_data + _size); };

  const_iterator end() const { return const_iterator(_data + _size); };

  reverse_iterator rbegin() { return reverse_iterator(end()); };

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() { return reverse_iterator(begin()); };

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  // Capacity

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

  void resize(size_type n, value_type val = value_type()) {
    if (n > _capacity) {
      reserve(n << 1);
    }
    for (size_type i = _size; i < n; i++) {
      _alloc.construct(_data + i, val);
    }
    _size = n;
  };

  size_type capacity() const { return _capacity; }

  bool empty() const { return _size == 0; }

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

  // Element access

  reference operator[](size_type n) { return _data[n]; }

  const_reference operator[](size_type n) const { return _data[n]; }

  reference at(size_type n) {
    if (n >= _size) {
      throw std::out_of_range("Index out of range");
    }
    return _data[n];
  }

  const_reference at(size_type n) const {
    if (n >= _size) {
      throw std::out_of_range("Index out of range");
    }
    return _data[n];
  }

  reference front() { return _data[0]; }

  const_reference front() const { return _data[0]; }

  reference back() { return _data[_size - 1]; }

  const_reference back() const { return _data[_size - 1]; }

  // Modifiers

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _alloc.deallocate(_data, _capacity);
    _size = 0;
    _capacity = 0;
    _data = NULL;
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  void assign(size_type n, const value_type &val) {
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_data + i);
    }
    _alloc.deallocate(_data, _capacity);
    _size = n;
    _capacity = n;
    _data = _alloc.allocate(n * sizeof(value_type));
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_data + i, val);
    }
  }

  void push_back(const value_type &val) {
    if (_size == _capacity) {
      reserve(_capacity << 1);
    }
    _alloc.construct(_data + _size, val);
    _size++;
  };

  void pop_back() {
    if (_size > 0) {
      _alloc.destroy(_data + _size - 1);
      _size--;
    }
  };

  iterator insert(iterator position, const value_type &val) {
    if (_size == _capacity) {
      reserve(_capacity << 1);
    }
    for (size_type i = _size; i > position - _data; i--) {
      _alloc.construct(_data + i, _data[i - 1]);
    }
    _alloc.construct(_data + position - _data, val);
    _size++;
    return position;
  };

  void insert(iterator position, size_type n, const value_type &val) {
    if (_size + n > _capacity) {
      reserve(_capacity << 1);
    }
    for (size_type i = _size; i > position - _data; i--) {
      _alloc.construct(_data + i, _data[i - 1]);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + position - _data + i, val);
    }
    _size += n;
  };

  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    size_type n = last - first;
    if (_size + n > _capacity) {
      reserve(_capacity << 1);
    }
    for (size_type i = _size; i > position - _data; i--) {
      _alloc.construct(_data + i, _data[i - 1]);
    }
    for (size_type i = 0; i < n; i++) {
      _alloc.construct(_data + position - _data + i, *(first + i));
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
    std::swap(_data, x._data);
    std::swap(_size, x._size);
    std::swap(_capacity, x._capacity);
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
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < rhs.size(); i++) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

} // namespace ft

#endif
