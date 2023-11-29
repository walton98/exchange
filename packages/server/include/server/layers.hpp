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
  sequencer(F &&f, uint64_t next_seq_num = 0)
      : f_{std::move(f)}, next_seq_num_{next_seq_num} {}

  void operator()(uint64_t seq_num, const T &payload) {
    if (seq_num == next_seq_num_) {
      spdlog::debug("Got message with seqnum: {}", seq_num);
      f_(payload);
      // TODO: drain from queue
      ++next_seq_num_;
    } else {
      spdlog::warn("Skipping message: got {}, expected {}", seq_num,
                   next_seq_num_);
      // TODO: add to queue
    }
  }

private:
  F f_;
  uint64_t next_seq_num_;
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
