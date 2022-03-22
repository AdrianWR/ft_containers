#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft {

/**
 * @brief Base class for standard binary function objects.
 * @tparam Arg1 Type of the first argument.
 * @tparam Arg2 Type of the second argument.
 * @tparam Result Type of the result.
 */
template <class Arg1, class Arg2, class Result> struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

/**
 * @brief Binary function object class whose call returns whether
 * its first argument compares less than the second (as returned by operator <).
 * @tparam T Type of the arguments.
 */
template <class T> struct less : binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x < y; }
};

} // namespace ft

#endif
