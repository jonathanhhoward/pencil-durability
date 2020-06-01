# Pencil Durability Kata

This repository contains my original solution to the [Pencil Durability Kata](https://github.com/PillarTechnology/kata-pencil-durability) for Pillar Technology.
The source code is written in C++17 and the tests use the [Catch2](https://github.com/catchorg/Catch2) framework.

### Required Dependencies

- C++17 compiler included in the system PATH
  - Linux and Mac may use GCC or Clang
  - Windows may use MSVC, Cygwin, or MinGW

- Gradle - to build and run the tests

- Java - to run Gradle

- Catch2 - included with the source code

### Build and run the tests

At the command line type:
```
$ git clone https://github.com/jonathanhhoward/pencil-durability.git
$ cd pencil-durability
$ gradle test
```
The tests will build and run. When the tests complete you should see the following output:

```
===============================================================================
All tests passed (39 assertions in 7 test cases)
```

You may have to scroll up to see this.

### Navigating the source code

The test code is at `./src/test/cpp/pencil-durability-tests.cpp`

The Catch2 framework code is at `./src/test/headers/catch.hpp` and `./src/test/cpp/catch-main.cpp`

The starting point of the kata code is at `./src/main/headers/Pencil.h`

The remainder of the kata code is dispersed between `./src/main/headers/` and `./src/main/cpp/`