#include <print>
#include <vector>

#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>
#include <asio/redirect_error.hpp>
#include <asio/use_awaitable.hpp>

namespace network {

class producer {
public:
  producer(asio::io_context &ioc, std::string_view host, std::string_view port)
      : socket_{ioc, asio::ip::udp::endpoint{asio::ip::udp::v4(), 0}},
        endpoint_{*asio::ip::udp::resolver(ioc).resolve(asio::ip::udp::v4(),
                                                        host, port)} {}

  asio::awaitable<void> produce(std::vector<char> data) {
    asio::error_code ec;
    co_await socket_.async_send_to(
        asio::buffer(data), endpoint_,
        asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
      std::println("Error processing message: {}", ec.message());
    }
  }

private:
  asio::ip::udp::socket socket_;
  asio::ip::udp::endpoint endpoint_;
};

} // namespace network