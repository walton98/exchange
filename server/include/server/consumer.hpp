#ifndef SERVER_CONSUMER_HPP
#define SERVER_CONSUMER_HPP

#include <exception>

#include <asio/awaitable.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>

namespace server {

class consumer {
  asio::io_context &ioc_;
  asio::ip::udp::endpoint ep_;
  bool shutdown_;

  asio::awaitable<void> accept_coro();
  void accept_error(std::exception_ptr &);
  virtual void handle_message(char data[]) {}

public:
  consumer(asio::io_context &ioc)
      : ioc_{ioc}, ep_{asio::ip::udp::v4(), 8080}, shutdown_{false} {}
  void start();
};

} // namespace server

#endif // SERVER_CONSUMER_HPP
