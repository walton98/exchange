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

add_library(server server/src/consumer.cpp)
target_include_directories(server PUBLIC server/include)
target_link_libraries(server PRIVATE asio::asio)
add_library(exchange::server ALIAS server)

add_executable(meng meng/src/main.cpp)
target_include_directories(meng PRIVATE meng/include)
target_link_libraries(
  meng
  PRIVATE
  asio::asio
  Threads::Threads
  server)
