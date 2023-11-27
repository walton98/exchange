add_library(server INTERFACE)
target_include_directories(server INTERFACE include)
target_link_libraries(
  server
  INTERFACE
  spdlog::spdlog
  exchange::protos)
add_library(exchange::server ALIAS server)
