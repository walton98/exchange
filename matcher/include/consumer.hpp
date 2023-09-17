#ifndef MATCHER_CONSUMER_HPP
#define MATCHER_CONSUMER_HPP

#include <iostream>
#include <string>

#include <matcher.pb.h>
#include <server/consumer.hpp>

#include "ring_buffer.hpp"

namespace matcher {

template <class RingBuf>
class consumer : public server::consumer<consumer<RingBuf>> {
public:
  friend server::consumer<consumer>;

  consumer(asio::io_context &ioc, asio::ip::port_type port,
           std::string &multicast_address, producer<RingBuf> prod)
      : server::consumer<consumer>(ioc, port, multicast_address), prod_{prod} {}

  void handle_message(const std::string &data) {
    matcher_proto::Book book;
    if (!book.ParseFromString(data)) {
      std::cout << "could not parse message" << std::endl;
      return;
    }
    // send to ring buffer
    prod_.produce_one(book);
    prod_.commit();
  }

private:
  producer<RingBuf> prod_;
};

} // namespace matcher

#endif // MATCHER_CONSUMER_HPP