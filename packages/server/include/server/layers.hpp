#ifndef SERVER_LAYERS_HPP
#define SERVER_LAYERS_HPP

#include <cstdint>
#include <string>
#include <utility>

#include <matcher.pb.h>
#include <spdlog/spdlog.h>

namespace server {

template <typename F, typename T> class sequencer {
public:
  explicit sequencer(F &&f) : f_{std::move(f)} {}

  void operator()(uint64_t seq_num, const T &payload) {
    spdlog::debug("Got message with seqnum: {}", seq_num);
    f_(payload);
  }

private:
  F f_;
};

template <typename F> class decoder {
public:
  explicit decoder(F &&f) : f_{std::move(f)} {}

  void operator()(const std::string &data) {
    matcher_proto::Envelope envelope;
    if (!envelope.ParseFromString(data)) {
      spdlog::warn("Could not parse message");
      return;
    }
    f_(envelope.seq_num(), envelope.action());
  }

private:
  F f_;
};

} // namespace server

#endif
