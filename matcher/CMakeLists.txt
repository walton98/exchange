add_library(matcher_lib src/engine.cpp)
target_include_directories(matcher_lib PUBLIC include)
target_link_libraries(
  matcher_lib
  PUBLIC
  Threads::Threads
  exchange::server
  exchange::protos)

add_executable(matcher src/main.cpp)
target_link_libraries(matcher PRIVATE matcher_lib)
add_executable(exchange::matcher ALIAS matcher)


add_executable(matcher_test test/test.cpp)
target_link_libraries(
  matcher_test
  PRIVATE
  Catch2::Catch2WithMain
  matcher_lib)
catch_discover_tests(matcher_test)