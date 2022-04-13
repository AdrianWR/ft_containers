#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T>> class stack {

public:
  typedef T value_type;
  typedef Container container_type;
  typedef typename Container::size_type size_type;

  template <typename T1, typename Container1>
  friend bool operator==(const stack<T1, Container1> &,
                         const stack<T1, Container1> &);

  template <typename T1, typename Container1>
  friend bool operator<(const stack<T1, Container1> &,
                        const stack<T1, Container1> &);

protected:
  Container _container;

public:
  /**
   * @brief Construct a new stack object
   *
   * @param container The container to use as the underlying data structure
   */
  explicit stack(const container_type &ctnr = container_type())
      : _container(ctnr) {}

  /**
   * @brief Check if the stack is empty
   */
  bool empty() const { return _container.empty(); }

  /**
   * @brief Get the size of the stack
   */
  size_type size() const { return _container.size(); }

  /**
   * @brief Get the top element of the stack
   */

  value_type &top() { return _container.back(); }

  const value_type &top() const { return _container.back(); }

  /**
   * @brief Push an element onto the stack
   *
   * @param value The value to push onto the stack
   */
  void push(const value_type &value) { _container.push_back(value); }

  /**
   * @brief Pop an element off the stack
   */
  void pop() { _container.pop_back(); }
};

template <class T, class Container>
bool operator==(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return lhs._container == rhs._container;
}

template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return lhs._container < rhs._container;
}

template <class T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return !(rhs < lhs);
}

template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return !(lhs < rhs);
}

} // namespace ft

#endif
