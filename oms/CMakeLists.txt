add_library(
  oms_lib
  src/engine.cpp
  src/request.cpp)
target_include_directories(oms_lib PUBLIC include)
target_link_libraries(
  oms_lib
  PUBLIC
  Boost::serialization
  spdlog::spdlog
  Threads::Threads
  exchange::common
  exchange::protos
  exchange::ring_buffer
  exchange::network)

add_executable(oms src/main.cpp)
target_link_libraries(oms PRIVATE oms_lib)
add_executable(exchange::oms ALIAS oms)
