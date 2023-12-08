add_library(
  protos
  src/envelope.pb.cc
  src/matcher.pb.cc
  src/oms.pb.cc
  src/types.pb.cc)
set_target_properties(protos PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(protos PUBLIC src)
target_link_libraries(protos PRIVATE protobuf::libprotobuf)
add_library(exchange::protos ALIAS protos)
