cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  meng
  VERSION
  1.0
  LANGUAGES CXX C)

find_package(asio CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_executable(meng src/main.cpp src/consumer.cpp)

target_include_directories(meng PRIVATE include)

target_link_libraries(meng PRIVATE asio::asio Threads::Threads)
