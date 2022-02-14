cmake_minimum_required(VERSION 3.22)

project(ft_containers)

# Build type configuration
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "${default_build_type}")
endif()
message(STATUS "Build type: '${CMAKE_BUILD_TYPE}'")

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Werror -std=c++98 -pedantic")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)
enable_testing()
add_test( NAME Test COMMAND Test )
