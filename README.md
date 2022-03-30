# ft_containers

[![build](https://github.com/AdrianWR/ft_containers/actions/workflows/cmake.yml/badge.svg)](https://github.com/AdrianWR/ft_containers/actions/workflows/cmake.yml)
[![lint](https://github.com/AdrianWR/ft_containers/actions/workflows/lint.yml/badge.svg)](https://github.com/AdrianWR/ft_containers/actions/workflows/lint.yml)

A custom implementation of some classic C++ containers

## Prerequisites

- CMake on version 3.22, at least;
- A compatible C++ compiler, with support to C++98.

## Running Unit Tests

The CMake targets are already configured to build the tests available at the `test` directory. I suggest you to take a look in there to understand a bit more the containers behavior. To build and run the tests, execute the following commands.

```shell
cmake -S . -B build
cmake --build build
build/test/FtContainersTests
```
