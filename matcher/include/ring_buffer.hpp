#ifndef MATCHER_RING_BUFFER_HPP
#define MATCHER_RING_BUFFER_HPP

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>

#include <iostream>

namespace matcher {

template <class T, uint16_t Size> class ring_buffer {
public:
  using value_type = T;
  using size_type = decltype(Size);

  ring_buffer() : buf_{} {}

  constexpr auto size() const noexcept { return Size; }

  value_type &operator[](size_type pos) noexcept { return buf_[pos % size()]; }

  constexpr const value_type &operator[](size_type pos) const noexcept {
    return buf_[pos % size()];
  }

private:
  std::array<T, Size> buf_;
};

template <class RingBuf> class ring_buffer_iterator {
public:
  ring_buffer_iterator(const RingBuf &buf, int64_t pos)
      : buf_{&buf}, current_{pos} {}

  void operator++() { current_++; }

  const typename RingBuf::value_type &operator*() const {
    return (*buf_)[current_];
  }

  bool operator==(ring_buffer_iterator &other) {
    return current_ == other.current_;
  }

private:
  const RingBuf *buf_;
  int64_t current_;
};

class cursor {
public:
  using pos_type = int64_t;
  static_assert(std::atomic<pos_type>::is_always_lock_free);

  cursor() : pos_{0} {}

  void follow(std::shared_ptr<cursor> following) {
    following_ = std::move(following);
  }

  void unfollow() { following_ = nullptr; }

  std::shared_ptr<cursor> following() const noexcept { return following_; }

  pos_type pos() const noexcept { return pos_.load(std::memory_order_acquire); }

  // Wait for this cursor to be finished with a position.
  // Returns one past the maximum available position
  // (may be higher than required_pos).
  auto wait_for_pos(pos_type required_pos) {
    while (true) {
      auto current_pos = pos();
      if (current_pos > required_pos) {
        return current_pos;
      }
      std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
  }

  void move_to(pos_type new_pos) {
    pos_.store(new_pos, std::memory_order_release);
  }

private:
  std::shared_ptr<cursor> following_;
  // points to the position to be used next,
  // any value below this is free to be used
  // by any followers.
  std::atomic<pos_type> pos_;
};

struct cursor_pair {
  std::shared_ptr<cursor> prod_cursor;
  std::shared_ptr<cursor> cons_cursor;

  cursor_pair()
      : prod_cursor{std::make_shared<matcher::cursor>()},
        cons_cursor{std::make_shared<matcher::cursor>()} {
    prod_cursor->follow(cons_cursor);
    cons_cursor->follow(prod_cursor);
  }

  void unlink() {
    prod_cursor->unfollow();
    cons_cursor->unfollow();
  }
};

template <class RingBuf> class producer {
public:
  producer(RingBuf &buf, std::shared_ptr<cursor> prod_cursor)
      : buf_{&buf}, current_{}, end_{0}, cursor_{std::move(prod_cursor)} {}

  void claim(int64_t n) {
    // Wait until we won't overwrite data that the
    // consumer has not read yet.
    auto required_position = current_ + n - (*buf_).size() - 1;
    if (end_ > required_position) {
      return;
    }
    end_ = cursor_->following()->wait_for_pos(required_position);
  }

  void produce_one(typename RingBuf::value_type val) {
    claim(1);
    (*buf_)[current_] = std::move(val);
    ++current_;
  }

  // Note that batch size before commit must be less
  // than the buffer size.
  // TODO: add assertion for this
  void commit() { cursor_->move_to(current_); }

private:
  RingBuf *buf_;
  // Local copy of cursor which we increment until committing.
  cursor::pos_type current_;
  // Store the last known follower position so that we
  // don't have to query it as often.
  cursor::pos_type end_;
  std::shared_ptr<cursor> cursor_;
};

template <class RingBuf> class iterate_batch {
public:
  iterate_batch(const RingBuf &buf, cursor::pos_type start_pos,
                cursor::pos_type end_pos)
      : buf_{&buf}, start_pos_{start_pos}, end_pos_{end_pos} {}

  ring_buffer_iterator<RingBuf> begin() const noexcept {
    return {*buf_, start_pos_};
  }

  ring_buffer_iterator<RingBuf> end() const noexcept {
    return {*buf_, end_pos_};
  }

private:
  const RingBuf *buf_;
  cursor::pos_type start_pos_;
  cursor::pos_type end_pos_;
};

// no end to buffer
class faux_end {};

/// Iterates over ring buffer, returning batch iterators
template <class RingBuf> class batch_iterator {
public:
  // TODO: assert buf_size > max_batch_size
  batch_iterator(const RingBuf &buf, std::shared_ptr<cursor> cons_curs,
                 typename RingBuf::size_type max_batch_size)
      : buf_{&buf}, curs_{std::move(cons_curs)},
        max_batch_size_{max_batch_size}, batch_start_{0}, batch_end_{0} {
    wait_for_batch();
  }

  iterate_batch<RingBuf> operator*() const {
    return {*buf_, batch_start_, batch_end_};
  }

  void operator++() {
    commit_batch();
    batch_start_ = batch_end_;
    wait_for_batch();
  }

  bool operator==(const faux_end &) const noexcept { return false; }

private:
  const RingBuf *buf_;
  std::shared_ptr<cursor> curs_;
  typename RingBuf::size_type max_batch_size_;
  cursor::pos_type batch_start_;
  cursor::pos_type batch_end_;

  void wait_for_batch() {
    auto max_end = curs_->following()->wait_for_pos(batch_start_);
    auto batch_size = std::min(max_end - batch_start_,
                               static_cast<cursor::pos_type>(max_batch_size_));
    batch_end_ = batch_start_ + batch_size;
  }

  void commit_batch() { curs_->move_to(batch_end_); }
};

template <class RingBuf> class batch_iterate {
public:
  batch_iterate(const RingBuf &buf, std::shared_ptr<cursor> cons_curs,
                typename RingBuf::size_type max_batch_size)
      : buf_{&buf}, curs_{std::move(cons_curs)},
        max_batch_size_{max_batch_size} {}

  batch_iterator<RingBuf> begin() noexcept {
    return {*buf_, curs_, max_batch_size_};
  };
  faux_end end() noexcept { return {}; };

private:
  const RingBuf *buf_;
  std::shared_ptr<cursor> curs_;
  typename RingBuf::size_type max_batch_size_;
};

} // namespace matcher

#endif
