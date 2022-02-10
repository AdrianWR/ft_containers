# ft_containers

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
