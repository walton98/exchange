#ifndef MENG_RING_BUFFER_HPP
#define MENG_RING_BUFFER_HPP

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>

#include <iostream>

namespace meng {

template <class T, int Size> class ring_buffer {
public:
  using value_type = T;
  using size_type = decltype(Size);

  ring_buffer() : buf_{} {}

  constexpr auto size() const noexcept { return Size; }

  constexpr value_type &operator[](size_type pos) noexcept {
    return buf_[pos % size()];
  }

private:
  std::array<T, Size> buf_;
};

class cursor {
public:
  using pos_type = int64_t;
  static_assert(std::atomic<pos_type>::is_always_lock_free);

  cursor() : pos_{} {}

  pos_type pos() const noexcept { return pos_.load(std::memory_order_acquire); }

  // returns last available position
  auto wait_for_pos(pos_type required_pos) {
    while (true) {
      auto current_pos = pos();
      if (current_pos > required_pos) {
        return current_pos - 1;
      }
      std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
  }

  void move_to(pos_type new_pos) {
    pos_.store(new_pos, std::memory_order_release);
  }

private:
  std::atomic<pos_type> pos_;
};

template <class RingBuf>
class producer {
public:
  producer(RingBuf &buf, std::shared_ptr<cursor> cons_cursor,
           std::shared_ptr<cursor> prod_cursor)
      : buf_{buf}, current_{}, end_{0},
        cursor_{std::move(prod_cursor)}, following_{std::move(cons_cursor)} {}

  void claim(int64_t n) {
    // wait until we won't overwrite data that the
    // consumer has not read yet
    auto required_position = current_ + n - buf_.size();
    std::cout << "producer end: " << end_ << std::endl;
    std::cout << "required pos: " << required_position << std::endl;
    if (end_ > required_position) {
      return;
    }
    end_ = following_->wait_for_pos(required_position);
    std::cout << "producer end after wait: " << end_ << std::endl;
  }

  void produce_one(typename RingBuf::value_type val) {
    claim(1);
    buf_[current_] = std::move(val);
    ++current_;
  }

  // note that batch size before commit must be less
  // than the buffer size.
  // TODO: add assertion for this
  void commit() { cursor_->move_to(current_); }

private:
  RingBuf &buf_;
  // local copy of cursor which we increment until committing
  int64_t current_;
  // store the last known follower position so that we
  // don't have to query it as often
  int64_t end_;
  std::shared_ptr<cursor> cursor_;
  std::shared_ptr<cursor> following_;
};

// no end to buffer
class faux_end {};

template <class RingBuf>
class batch_iterator {
public:
  // TODO: assert buf_size > max_batch_size
  batch_iterator(RingBuf &buf, std::shared_ptr<cursor> cons_curs,
                 std::shared_ptr<cursor> prod_curs, int max_batch_size)
      : buf_{buf}, cons_curs_{std::move(cons_curs)}, prod_curs_{std::move(prod_curs)},
        max_batch_size_{max_batch_size}, current_{0}, batch_end_{0} {
    wait_for_batch();
  }

  auto operator*() const {
    return buf_[current_];
  }

  void operator++() {
    ++current_;
    if (current_ > batch_end_) {
      commit_batch();
      wait_for_batch();
    }
  }

  bool operator==(const faux_end &) const noexcept { return false; }
  
private:
  RingBuf &buf_;
  std::shared_ptr<cursor> cons_curs_;
  std::shared_ptr<cursor> prod_curs_;
  int max_batch_size_;
  cursor::pos_type current_;
  cursor::pos_type batch_end_;

  void wait_for_batch() {
    batch_end_ = prod_curs_->wait_for_pos(current_);
    std::cout << "consumer end: " << batch_end_ << std::endl;
  }

  void commit_batch() { cons_curs_->move_to(batch_end_); }
};

template <class RingBuf>
class batch_iterate {
public:
  batch_iterate(RingBuf &buf, std::shared_ptr<cursor> cons_curs,
                std::shared_ptr<cursor> prod_curs, int max_batch_size) 
      : buf_{buf}, cons_curs_{std::move(cons_curs)}, prod_curs_{std::move(prod_curs)},
        max_batch_size_{max_batch_size} {}

  batch_iterator<RingBuf> begin() noexcept { return {buf_, cons_curs_, prod_curs_, max_batch_size_}; };
  faux_end end() noexcept { return {}; };

private:
  RingBuf &buf_;
  std::shared_ptr<cursor> cons_curs_;
  std::shared_ptr<cursor> prod_curs_;
  int max_batch_size_;
};

} // namespace meng

#endif
