cmake_minimum_required(VERSION 3.22)

project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++98 -pedantic")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(test)
