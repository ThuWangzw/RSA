cmake_minimum_required(VERSION 3.15)
project(RSA)

set(CMAKE_CXX_STANDARD 14)

add_executable(RSA main.cpp Integer.cpp Integer.h RSA.cpp RSA.h)