#include "consumer.hpp"

namespace meng {

void consumer::handle_message(const std::string &data) {
  meng_proto::Book book;
  if (!book.ParseFromString(data)) {
    std::cout << "could not parse message" << std::endl;
    return;
  }
  std::cout << book.id() << std::endl;
}

} // namespace meng
