#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

template <class Iterator> class reverse_iterator {
public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference reference;
  typedef typename ft::iterator_traits<iterator_type>::difference_type
      difference_type;
  typedef typename ft::iterator_traits<iterator_type>::iterator_category
      iterator_category;

  reverse_iterator() : _it() {}

  explicit reverse_iterator(iterator_type it) : _it(it) {}

  template <class Iter>
  reverse_iterator(const reverse_iterator<Iter> &rev_it) : _it(rev_it.base()) {}

  ~reverse_iterator() {}

  iterator_type base() const { return _it; }

  reference operator*() const {
    iterator_type tmp = _it;
    return *--tmp;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(_it - n);
  }

  reverse_iterator &operator++() {
    --_it;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  reverse_iterator &operator+=(difference_type n) {
    _it -= n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_it + n);
  }

  reverse_iterator &operator--() {
    ++_it;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type n) const { return base()[-n - 1]; }

private:
  iterator_type _it;
};

template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return !(lhs == rhs);
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
  return rhs.base() > lhs.base();
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return rhs.base() >= lhs.base();
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
  return rhs.base() < lhs.base();
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
  return rhs.base() <= lhs.base();
}

template <class Iterator>
reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator> &it) {
  return it + n;
}

template <class Iterator>
reverse_iterator<Iterator>
operator-(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator> &it) {
  return it - n;
}

} // namespace ft

#endif
