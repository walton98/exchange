cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  exchange
  VERSION
  1.0
  LANGUAGES CXX C)

find_package(asio CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(server)
add_subdirectory(meng)
