cmake_minimum_required(VERSION 3.16)
project(pencil_durability)

set(CMAKE_CXX_STANDARD 17)

add_executable(pencil_durability catch-main.cpp pencil-durability-tests.cpp Pencil.cpp Point.cpp Eraser.cpp)