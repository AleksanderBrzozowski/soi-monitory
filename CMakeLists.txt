cmake_minimum_required(VERSION 3.9)
project(monitory_soi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(monitory_soi main.cpp Buffer.cpp Buffer.h)
