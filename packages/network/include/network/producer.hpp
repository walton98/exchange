#include <print>
#include <span>

#include <asio/awaitable.hpp>
#include <asio/deferred.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>

#include "as_expected.hpp"

namespace network {

class producer {
public:
  producer(asio::io_context &ioc, std::string_view host, std::string_view port)
      : socket_{ioc, asio::ip::udp::endpoint{asio::ip::udp::v4(), 0}},
        endpoint_{*asio::ip::udp::resolver(ioc).resolve(asio::ip::udp::v4(),
                                                        host, port)} {}

  asio::awaitable<void> produce(std::span<char> data) {
    auto result = co_await socket_.async_send_to(
        asio::buffer(data), endpoint_, network::as_expected(asio::deferred));
    if (!result.has_value()) {
      std::println("Error processing message: {}", result.error().message());
    }
  }

private:
  asio::ip::udp::socket socket_;
  asio::ip::udp::endpoint endpoint_;
};

} // namespace network
