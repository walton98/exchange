add_executable(meng src/main.cpp)
target_include_directories(meng PRIVATE include)
target_link_libraries(
  meng
  PRIVATE
  asio::asio
  Threads::Threads
  exchange::server)
add_executable(exchange::meng ALIAS meng)
