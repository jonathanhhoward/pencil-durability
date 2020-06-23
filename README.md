# Pencil Durability Kata

This repository contains my original solution to the [Pencil Durability Kata](https://github.com/PillarTechnology/kata-pencil-durability) for Pillar Technology.
The source code is written in C++17 and the tests use the [Catch2](https://github.com/catchorg/Catch2) framework.

### Navigating the source code

The the test code is at `./src/test/cpp/`

The Catch2 framework code is at `./src/test/headers/catch.hpp` and `./src/test/cpp/catch-main.cpp`

The starting point of the kata code is at `./src/main/headers/Writer.h`

The remainder of the kata code is dispersed between `./src/main/headers/` and `./src/main/cpp/`

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
All tests passed (77 assertions in 18 test cases)
```

You may have to scroll up to see this.

### Required dependencies
versions are minimums

- C++17 compiler included in the system PATH
  - Linux
    - GCC 7
    - Clang 4
  - Mac OS
    - Apple Clang 10
    - GCC 7
  - Windows
    - MSVC 19.10 (VS 2017 15.0)
    - GCC 7 (Cygwin or MinGW)

- Gradle 5.5.1 - to build and run the tests

- JDK 8 - to run Gradle

- Catch2 - included with the source code
