cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# ASIO currently doesn't detect coroutine support
# since it only checks for the existence of the
# removed <experimental/coroutine> header.
# https://github.com/chriskohlhoff/asio/pull/1145
add_compile_definitions(ASIO_HAS_CO_AWAIT ON)

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

find_package(Catch2 3 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(server)
add_subdirectory(protos)
add_subdirectory(meng)
