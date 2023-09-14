#ifndef SERVER_CONSUMER_HPP
#define SERVER_CONSUMER_HPP

#include <exception>
#include <iostream>
#include <string>

#include <asio/awaitable.hpp>
#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/multicast.hpp>
#include <asio/ip/udp.hpp>
#include <asio/redirect_error.hpp>

namespace server {

template <class Derived> class consumer {
  /**
   * UDP multicast reciever.
   * Users must implement `void handle_message(char data[])`.
   */
  asio::io_context &ioc_;
  asio::ip::udp::endpoint ep_;
  asio::ip::udp::socket socket_;
  asio::ip::address multicast_address_;
  bool shutdown_;
  static constexpr int max_size_ = 1024;

  asio::awaitable<void> accept_coro() {
    socket_.open(ep_.protocol());
    socket_.set_option(asio::ip::udp::socket::reuse_address(true));
    socket_.bind(ep_);
    socket_.set_option(asio::ip::multicast::join_group(multicast_address_));
    while (!shutdown_) {
      std::array<char, max_size_> data{};
      asio::ip::udp::endpoint remote_endpoint_;
      asio::error_code ec;
      co_await socket_.async_receive_from(
          asio::buffer(data, max_size_), remote_endpoint_,
          asio::redirect_error(asio::use_awaitable, ec));
      if (ec) {
        std::cout << "error processing message: " << ec.message() << std::endl;
        continue;
      }
      static_cast<Derived *>(this)->handle_message(std::string(data.data()));
    }
    std::cout << "shutting down" << std::endl;
    socket_.close();
  }

  void accept_error(std::exception_ptr &eptr) {
    if (socket_.is_open()) {
      socket_.close();
    }
    try {
      std::rethrow_exception(eptr);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      ;
    }
  }

public:
  consumer(asio::io_context &ioc, asio::ip::port_type port,
           std::string &multicast_address)
      : ioc_{ioc}, ep_{asio::ip::udp::v4(), port}, socket_{ioc},
        multicast_address_{asio::ip::make_address(multicast_address)},
        shutdown_{false} {}

  void start() {
    asio::co_spawn(
        ioc_,
        [&]() {
          // start accepting new connections
          return accept_coro();
        },
        [&](std::exception_ptr eptr) {
          if (eptr) {
            return accept_error(eptr);
          }
        });
  }
};

} // namespace server

#endif // SERVER_CONSUMER_HPP
