#include "type_traits.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Disclaimer: I haven't found a way to test ft::enable_if
// with gtest, as it's a resource to be used within template
// metaprogramming. The template function available on the header
// file was copy-pasted from the documentation of the C++11 standard.
//
// Source: http://en.cppreference.com/w/cpp/types/enable_if

TEST(TestIsIntegral, TestIsIntegralTrue) {
  ASSERT_TRUE(ft::is_integral<bool>::value == true);
  ASSERT_TRUE(ft::is_integral<char>::value == true);
  ASSERT_TRUE(ft::is_integral<char16_t>::value == true);
  ASSERT_TRUE(ft::is_integral<char32_t>::value == true);
  ASSERT_TRUE(ft::is_integral<wchar_t>::value == true);
  ASSERT_TRUE(ft::is_integral<signed char>::value == true);
  ASSERT_TRUE(ft::is_integral<short>::value == true);
  ASSERT_TRUE(ft::is_integral<int>::value == true);
  ASSERT_TRUE(ft::is_integral<long>::value == true);
  ASSERT_TRUE(ft::is_integral<long long>::value == true);
  ASSERT_TRUE(ft::is_integral<unsigned char>::value == true);
  ASSERT_TRUE(ft::is_integral<unsigned short>::value == true);
  ASSERT_TRUE(ft::is_integral<unsigned int>::value == true);
  ASSERT_TRUE(ft::is_integral<unsigned long>::value == true);
  ASSERT_TRUE(ft::is_integral<unsigned long long>::value == true);
}

TEST(TestIsIntegral, TestIsIntegralFalse) {
  ASSERT_TRUE(ft::is_integral<float>::value == false);
  ASSERT_TRUE(ft::is_integral<double>::value == false);
  ASSERT_TRUE(ft::is_integral<long double>::value == false);
  ASSERT_TRUE(ft::is_integral<std::string>::value == false);
  ASSERT_TRUE(ft::is_integral<std::wstring>::value == false);
  ASSERT_TRUE(ft::is_integral<std::string *>::value == false);
  ASSERT_TRUE(ft::is_integral<std::wstring *>::value == false);
  ASSERT_TRUE(ft::is_integral<std::string &>::value == false);
  ASSERT_TRUE(ft::is_integral<std::wstring &>::value == false);
  ASSERT_TRUE(ft::is_integral<std::string &&>::value == false);
  ASSERT_TRUE(ft::is_integral<std::wstring &&>::value == false);
}
