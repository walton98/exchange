#ifndef NETWORK_AS_RESULT
#define NETWORK_AS_RESULT

/*
 * ASIO async_result adapter for std::expected.
 *
 * Adapted from:
 * https://www.boost.org/doc/libs/1_84_0/libs/outcome/doc/html/recipes/asio-integration-1-70.html
 * https://gist.github.com/cstratopoulos/901b5cdd41d07c6ce6d83798b09ecf9b
 *
 * Sample use:
 * ```
 * std::expected<std::size_t, asio::error_code> read =
 *     co_await socket.async_read(buffer, as_expected(asio::deferred));
 * ```
 */

#include <asio/associated_allocator.hpp>
#include <asio/associated_executor.hpp>
#include <asio/async_result.hpp>
#include <asio/detail/handler_alloc_helpers.hpp>
#include <asio/detail/handler_cont_helpers.hpp>
#include <asio/detail/handler_invoke_helpers.hpp>
#include <asio/error_code.hpp>

#include <expected>
#include <type_traits>
#include <utility>

namespace network {

template <typename CompletionToken> struct as_expected_t {
  CompletionToken token_;
};

template <typename CompletionToken>
inline auto as_expected(CompletionToken &&completion_token) {
  return as_expected_t<std::decay_t<CompletionToken>>{
      std::forward<CompletionToken>(completion_token)};
}

namespace detail {

// Class to adapt as_outcome_t as a completion handler
template <typename Handler> struct expected_result_handler {
  void operator()(const asio::error_code &ec) {
    using result_t = std::expected<void, asio::error_code>;

    if (ec) {
      handler_(result_t{std::unexpect, ec});
    } else {
      handler_(result_t{});
    }
  }

  template <typename T> void operator()(const asio::error_code &ec, T t) {
    using result_t = std::expected<T, asio::error_code>;

    if (ec) {
      handler_(result_t{std::unexpect, ec});
    } else {
      handler_(result_t{std::move(t)});
    }
  }

  Handler handler_;
};

template <typename Handler>
inline void *
asio_handler_allocate(std::size_t size,
                      expected_result_handler<Handler> *this_handler) {
  return asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
}

template <typename Handler>
inline void
asio_handler_deallocate(void *pointer, std::size_t size,
                        expected_result_handler<Handler> *this_handler) {
  asio_handler_alloc_helpers::deallocate(pointer, size, this_handler->handler_);
}

template <typename Handler>
inline bool
asio_handler_is_continuation(expected_result_handler<Handler> *this_handler) {
  return asio_handler_cont_helpers::is_continuation(this_handler->handler_);
}

template <typename Function, typename Handler>
inline void
asio_handler_invoke(Function &function,
                    expected_result_handler<Handler> *this_handler) {
  asio_handler_invoke_helpers::invoke(function, this_handler->handler_);
}

template <typename Function, typename Handler>
inline void
asio_handler_invoke(const Function &function,
                    expected_result_handler<Handler> *this_handler) {
  asio_handler_invoke_helpers::invoke(function, this_handler->handler_);
}

template <typename Signature> struct result_signature;

template <> struct result_signature<void(asio::error_code)> {
  using type = void(std::expected<void, asio::error_code>);
};

template <>
struct result_signature<void(const asio::error_code &)>
    : result_signature<void(asio::error_code)> {};

template <typename T> struct result_signature<void(asio::error_code, T)> {
  using type = void(std::expected<T, asio::error_code>);
};

template <typename T>
struct result_signature<void(const asio::error_code &, T)>
    : result_signature<void(asio::error_code, T)> {};

template <typename Signature>
using result_signature_t = typename result_signature<Signature>::type;

} // namespace detail

} // namespace network

namespace asio {

template <typename CompletionToken, typename Signature>
class async_result<::network::as_expected_t<CompletionToken>, Signature> {
public:
  using result_signature = ::network::detail::result_signature_t<Signature>;

  template <typename Initiation, typename... Args>
  static auto initiate(Initiation &&initiation,
                       ::network::as_expected_t<CompletionToken> &&token,
                       Args &&...args) {
    return async_initiate<CompletionToken, result_signature>(
        [init = std::forward<Initiation>(initiation)](
            auto &&handler, auto &&...callArgs) mutable {
          std::move(init)(
              ::network::detail::expected_result_handler<
                  std::decay_t<decltype(handler)>>{
                  std::forward<decltype(handler)>(handler)},
              std::forward<decltype(callArgs)>(callArgs)...);
        },
        token.token_, std::forward<Args>(args)...);
  }
};

template <typename Handler, typename Executor>
struct associated_executor<::network::detail::expected_result_handler<Handler>,
                           Executor> {
  using type = associated_executor<Handler, Executor>::type;

  static type get(const ::network::detail::expected_result_handler<Handler> &h,
                  const Executor &ex = Executor()) noexcept {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

template <typename Handler, typename Allocator>
struct associated_allocator<::network::detail::expected_result_handler<Handler>,
                            Allocator> {
  using type = associated_allocator<Handler, Allocator>::type;

  static type get(const ::network::detail::expected_result_handler<Handler> &h,
                  const Allocator &a = Allocator()) noexcept {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

} // namespace asio

#endif
