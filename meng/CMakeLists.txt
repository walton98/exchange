add_executable(meng src/main.cpp src/consumer.cpp)
target_include_directories(meng PRIVATE include)
target_link_libraries(
  meng
  PRIVATE
  asio::asio
  Threads::Threads
  exchange::server
  exchange::protos)
add_executable(exchange::meng ALIAS meng)
