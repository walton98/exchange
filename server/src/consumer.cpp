#include <exception>
#include <iostream>

#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/error_code.hpp>
#include <asio/redirect_error.hpp>
#include <asio/steady_timer.hpp>

#include "server/consumer.hpp"

namespace meng {

asio::awaitable<void> consumer::accept_coro() {
  asio::steady_timer backoff_timer_{ioc_};
  asio::ip::udp::socket socket{ioc_, ep_};
  while (!shutdown_) {
    char data[1024];
    asio::ip::udp::endpoint remote_endpoint_;
    asio::error_code ec;
    co_await backoff_timer_.async_wait(asio::use_awaitable);
    co_await socket.async_receive_from(
        asio::buffer(data, 1024), remote_endpoint_,
        asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
      std::cout << "failed accepting connection: " << ec.message() << std::endl;
      continue;
    }
    std::cout << "accepting connections: " << data << std::endl;
  }
  std::cout << "shutting down" << std::endl;
}

void consumer::accept_error(std::exception_ptr &eptr) {}

void consumer::start() {
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

} // namespace meng
