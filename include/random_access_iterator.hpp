/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:16:45 by aroque            #+#    #+#             */
/*   Updated: 2022/02/14 14:16:46 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

#include "nullptr.hpp"
#include <iterator>

namespace ft {

template <typename T>
class random_access_iterator
    : public ft::iterator<std::random_access_iterator_tag, T> {

public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;

public:
  random_access_iterator() : _ptr(ft::u_nullptr) {}

  random_access_iterator(pointer ptr) : _ptr(ptr) {}

  random_access_iterator(const random_access_iterator &i) : _ptr(i.ptr) {}

  random_access_iterator &operator=(const random_access_iterator &i) {
    if (this != &i)
      _ptr = i.ptr;
    return *this;
  }

  ~random_access_iterator() {}

  bool operator==(const random_access_iterator &i) const {
    return _ptr == i._ptr;
  }

  bool operator!=(const random_access_iterator &i) const {
    return _ptr != i._ptr;
  }

  reference operator*() const { return *_ptr; }

  pointer operator->() const { return _ptr; }

  random_access_iterator &operator++() {
    ++_ptr;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp(*this);
    ++_ptr;
    return tmp;
  }

  random_access_iterator &operator--() {
    --_ptr;
    return *this;
  }

  random_access_iterator operator--(int) {
    random_access_iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  random_access_iterator operator+(int n) const {
    random_access_iterator tmp(*this);
    tmp._ptr += n;
    return tmp;
  }

  random_access_iterator operator-(int n) const {
    random_access_iterator tmp(*this);
    tmp._ptr -= n;
    return tmp;
  }

  bool operator<(const random_access_iterator &i) const {
    return _ptr < i._ptr;
  }

  bool operator>(const random_access_iterator &i) const {
    return _ptr > i._ptr;
  }

  bool operator<=(const random_access_iterator &i) const {
    return _ptr <= i._ptr;
  }

  bool operator>=(const random_access_iterator &i) const {
    return _ptr >= i._ptr;
  }

  int operator-(const random_access_iterator &i) const { return _ptr - i._ptr; }

  random_access_iterator &operator+=(int n) {
    _ptr += n;
    return *this;
  }

  random_access_iterator &operator-=(int n) {
    _ptr -= n;
    return *this;
  }

  reference operator[](int n) const { return _ptr[n]; }

private:
  value_type *_ptr;
};

} // namespace ft

#endif
