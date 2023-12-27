add_library(network INTERFACE)
target_include_directories(network INTERFACE include)
target_link_libraries(
  network
  INTERFACE
  spdlog::spdlog
  exchange::protos)
add_library(exchange::network ALIAS network)
