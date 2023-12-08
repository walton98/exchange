#ifndef SERVER_LAYERS_HPP
#define SERVER_LAYERS_HPP

#include <cstdint>
#include <queue>
#include <string>
#include <utility>

#include <envelope.pb.h>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>

namespace server {

template <typename RingBuf, typename F> class queuer {
public:
  using Envelope = envelope_proto::Envelope;

  queuer(ring_buffer::producer<RingBuf> prod, F &&f)
      : prod_{std::move(prod)}, f_{f} {}

  void operator()(const Envelope &proto) {
    // TODO: handle unexpected
    auto parsed_action = f_(proto).value();

    // send to ring buffer
    prod_.produce_one(parsed_action);
    prod_.commit();
  }

private:
  ring_buffer::producer<RingBuf> prod_;
  F f_;
};

bool cmp(const envelope_proto::Envelope &lhs,
         const envelope_proto::Envelope &rhs) {
  return lhs.seq_num() > rhs.seq_num();
}

template <typename F> class sequencer {
public:
  using Envelope = envelope_proto::Envelope;

  sequencer(F &&f, uint64_t next_seq_num = 0)
      : f_{std::move(f)}, next_seq_num_{next_seq_num}, backlog_{cmp} {}

  void operator()(const Envelope &env) {
    if (env.seq_num() == next_seq_num_) {
      execute(env);
      drain_queue();
    } else if (env.seq_num() > next_seq_num_) {
      spdlog::debug("Adding message to backlog: got {}, expected {}",
                    env.seq_num(), next_seq_num_);
      backlog_.push(env);
      if (backlog_.size() > 16) {
        spdlog::warn("Queue is filling up, current size: {}", backlog_.size());
      }
    } else {
      spdlog::debug("Skipping old message: got {}, expected {}", env.seq_num(),
                    next_seq_num_);
    }
  }

private:
  F f_;
  uint64_t next_seq_num_;
  std::priority_queue<Envelope, std::vector<Envelope>,
                      std::function<bool(Envelope, Envelope)>>
      backlog_;

  void execute(const Envelope &env) {
    spdlog::debug("Executing message with seqnum: {}", env.seq_num());
    f_(env);
    ++next_seq_num_;
  }

  void drain_queue() {
    while (!backlog_.empty() && backlog_.top().seq_num() == next_seq_num_) {
      execute(backlog_.top());
      backlog_.pop();
    }
  }
};

template <typename F> class decoder {
public:
  explicit decoder(F &&f) : f_{std::move(f)} {}

  void operator()(const std::string &data) {
    envelope_proto::Envelope envelope;
    if (!envelope.ParseFromString(data)) {
      spdlog::warn("Could not parse message");
      return;
    }
    f_(envelope);
  }

private:
  F f_;
};

} // namespace server

#endif
