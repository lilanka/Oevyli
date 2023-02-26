cmake_minimum_required(VERSION 3.25)
project(Oevyli)

set(CMAKE_CXX_STANDARD 20)

add_executable(oevyli
  src/main.cc
  src/scanner.cc
  src/compiler.cc
  src/parser.cc
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)