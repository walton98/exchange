add_library(server INTERFACE)
target_include_directories(server INTERFACE include)
add_library(exchange::server ALIAS server)
