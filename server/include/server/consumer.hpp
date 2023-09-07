#ifndef SERVER_CONSUMER_HPP
#define SERVER_CONSUMER_HPP

#include <exception>
#include <string>

#include <asio/awaitable.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>

namespace server {

class consumer {
  asio::io_context &ioc_;
  asio::ip::udp::endpoint ep_;
  asio::ip::udp::socket socket_;
  asio::ip::address multicast_address_;
  bool shutdown_;

  asio::awaitable<void> accept_coro();
  void accept_error(std::exception_ptr &);
  virtual void handle_message(char data[]) {}

public:
  consumer(asio::io_context &ioc, asio::ip::port_type port, std::string multicast_address)
      : ioc_{ioc}, ep_{asio::ip::udp::v4(), port}, socket_{ioc},
        multicast_address_{asio::ip::make_address(multicast_address)}, shutdown_{false} {}
  void start();
};

} // namespace server

#endif // SERVER_CONSUMER_HPP
