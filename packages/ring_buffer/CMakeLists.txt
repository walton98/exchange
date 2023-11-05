add_library(ring_buffer INTERFACE)
target_include_directories(ring_buffer INTERFACE include)
add_library(exchange::ring_buffer ALIAS ring_buffer)

add_executable(ring_buffer_test test/test.cpp)
target_link_libraries(
  ring_buffer_test
  PRIVATE
  Catch2::Catch2WithMain
  ring_buffer)
catch_discover_tests(ring_buffer_test)
