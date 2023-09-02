#ifndef MENG_CONSUMER_HPP
#define MENG_CONSUMER_HPP

#include <exception>

#include <asio/awaitable.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>

namespace meng {

class consumer {
  asio::io_context &ioc_;
  asio::ip::udp::endpoint ep_;
  bool shutdown_;

  asio::awaitable<void> accept_coro();
  void accept_error(std::exception_ptr &);

public:
  consumer(asio::io_context &ioc)
      : ioc_{ioc}, ep_{asio::ip::udp::v4(), 8080}, shutdown_{false} {}
  void start();
};

} // namespace meng

#endif // MENG_CONSUMER_HPP
