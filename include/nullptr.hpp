#ifndef NULLPTR_HPP
#define NULLPTR_HPP

#include <cstddef>

namespace ft {

class nullptr_t {
public:
  template <class T> operator T *() const { return 0; }
  template <class C, class T> operator T C::*() const { return 0; }

private:
  void operator&() const;
};

const nullptr_t _nullptr = {};

} // namespace ft

#endif
