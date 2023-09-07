add_library(server src/consumer.cpp)
target_include_directories(server PUBLIC include)
target_link_libraries(server PRIVATE asio::asio)
add_library(exchange::server ALIAS server)
