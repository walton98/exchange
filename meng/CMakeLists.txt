add_library(meng_lib src/consumer.cpp)
target_include_directories(meng_lib PUBLIC include)
target_link_libraries(
  meng_lib
  PUBLIC
  Threads::Threads
  exchange::server
  exchange::protos)

add_executable(meng src/main.cpp)
target_link_libraries(meng PRIVATE meng_lib)
add_executable(exchange::meng ALIAS meng)


add_executable(meng_test test/test.cpp)
target_link_libraries(
  meng_test
  PRIVATE
  Catch2::Catch2WithMain
  meng_lib)
