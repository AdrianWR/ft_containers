#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft {

typedef std::ptrdiff_t ptrdiff_t;

typedef std::input_iterator_tag input_iterator_tag;

typedef std::output_iterator_tag output_iterator_tag;

typedef std::forward_iterator_tag forward_iterator_tag;

typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;

typedef std::random_access_iterator_tag random_access_iterator_tag;

template <class Category, class T, class Distance = ft::ptrdiff_t,
          class Pointer = T *, class Reference = T &>
class iterator {
public:
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template <class Iterator> class iterator_traits {
public:
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template <class T> class iterator_traits<T *> {
public:
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class T> class iterator_traits<const T *> {
public:
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

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
    --_it;
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
    ++_it;
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

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
__do_distance(InputIterator first, InputIterator last, ft::input_iterator_tag) {
  typename ft::iterator_traits<InputIterator>::difference_type result = 0;
  while (first != last) {
    ++first;
    ++result;
  }
  return result;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
__do_distance(InputIterator first, InputIterator last,
              ft::random_access_iterator_tag) {
  return last - first;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return __do_distance(
      first, last,
      typename ft::iterator_traits<InputIterator>::iterator_category());
}

} // namespace ft

#endif
