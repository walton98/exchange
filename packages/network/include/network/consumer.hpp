#ifndef NETWORK_CONSUMER_HPP
#define NETWORK_CONSUMER_HPP

#include <exception>
#include <iostream>
#include <print>
#include <string>

#include <asio/as_tuple.hpp>
#include <asio/awaitable.hpp>
#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/deferred.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/multicast.hpp>
#include <asio/ip/udp.hpp>

namespace network {

template <typename F> class consumer {
  /**
   * UDP multicast reciever.
   * Users must implement `void handle_message(char data[])`.
   */
  asio::io_context &ioc_;
  asio::ip::udp::endpoint ep_;
  asio::ip::udp::socket socket_;
  asio::ip::address multicast_address_;
  F f_;
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
      auto [ec, size] = co_await socket_.async_receive_from(
          asio::buffer(data, max_size_), remote_endpoint_,
          asio::as_tuple(asio::deferred));
      if (ec) {
        std::println("Error processing message: {}", ec.message());
        continue;
      }
      std::invoke(f_, std::string(data.data(), size));
    }
    std::println("Shutting down");
    socket_.close();
  }

  void accept_error(std::exception_ptr &eptr) {
    if (socket_.is_open()) {
      socket_.close();
    }
    try {
      std::rethrow_exception(eptr);
    } catch (std::exception &e) {
      std::println("Error: {}", e.what());
      ;
    }
  }

public:
  consumer(asio::io_context &ioc, asio::ip::port_type port,
           std::string_view multicast_address, F &&f)
      : ioc_{ioc}, ep_{asio::ip::udp::v4(), port}, socket_{ioc},
        multicast_address_{asio::ip::make_address(multicast_address)}, f_{f},
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

} // namespace network

#endif
