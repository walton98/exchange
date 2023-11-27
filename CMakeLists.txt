cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  exchange
  VERSION
  1.0
  LANGUAGES CXX C)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck REQUIRED)
list(
  APPEND CMAKE_CXX_CPPCHECK
  "--suppressions-list=${CMAKE_SOURCE_DIR}/.suppressions"
  "--error-exitcode=1"
)

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(Catch2 3 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(packages)
add_subdirectory(matcher)
