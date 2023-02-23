cmake_minimum_required(VERSION 3.25)
project(Oevyli)

set(CMAKE_CXX_STANDARD 20)
set(
  -std=c++20
  -fmodules-ts
  -xc++-system-header
  iostream
)

add_executable(oevyli
  src/main.cc
  src/scanner.cc
  src/compile.cc
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)