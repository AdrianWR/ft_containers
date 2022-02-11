#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {

template <class T, class Alloc = std::allocator<T>> class Vector {
  public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

  private:
    T *data;
    size_type _size;
    size_type _capacity;

  public:
    Vector() : _size(0){};

    Vector(unsigned int size, T value = 0) : _size(size) {
	data = Alloc::allocate(size);
	for (unsigned int i = 0; i < size; i++) {
	    data[i] = value;
	}
    }

    Vector(const Vector &);

    Vector &operator=(const Vector &);

    ~Vector(){};

    unsigned int size() const { return this->_size; };
};

} // namespace ft

#endif

