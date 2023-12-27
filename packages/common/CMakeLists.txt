add_library(common INTERFACE)
target_include_directories(common INTERFACE include)
target_link_libraries(
  common
  INTERFACE
  spdlog::spdlog
  exchange::ring_buffer
  exchange::network)
add_library(exchange::common ALIAS common)
