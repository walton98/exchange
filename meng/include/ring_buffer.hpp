#ifndef MENG_RING_BUFFER_HPP
#define MENG_RING_BUFFER_HPP

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>

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

  cursor() : pos_{} {}

  pos_type pos() const noexcept { return pos_.load(std::memory_order_acquire); }

  // returns last available position
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
  std::atomic<pos_type> pos_;
};

class producer {
public:
  template <class RingBuf>
  producer(std::shared_ptr<cursor> cons_cursor,
           std::shared_ptr<cursor> prod_cursor, RingBuf &buf)
      : size_{buf.size()}, current_{}, end_{buf.size()},
        cursor_{std::move(prod_cursor)}, following_{std::move(cons_cursor)} {}

  void claim(int64_t n) {
    // wait until we won't overwrite data that the
    // consumer has not read yet
    auto required_position = current_ + n - size_;
    if (end_ > required_position) {
      return;
    }
    end_ = following_->wait_for_pos(required_position);
  }

  template <class T, int Size>
  void produce_one(ring_buffer<T, Size> &buf, T val) {
    claim(1);
    buf[current_] = std::move(val);
    ++current_;
  }

  void commit() { cursor_->move_to(current_ + 1); }

private:
  // size of ring buffer
  int size_;
  // local copy of cursor which we increment until committing
  int64_t current_;
  // store the last known follower position so that we
  // don't have to query it as often
  int64_t end_;
  std::shared_ptr<cursor> cursor_;
  std::shared_ptr<cursor> following_;
};

class consumer {
public:
  template <class RingBuf>
  consumer(std::shared_ptr<cursor> cons_cursor,
           std::shared_ptr<cursor> prod_cursor, RingBuf &buf)
      : size_{buf.size()}, current_{}, end_{}, cursor_{std::move(cons_cursor)},
        following_{std::move(prod_cursor)} {}

  void claim(int64_t n) {
    // wait until we won't overwrite data that the
    // consumer has not read yet
    auto required_pos = current_ + n;
    if (end_ > required_pos) {
      return;
    }
    end_ = following_->wait_for_pos(required_pos);
  }

  template <class RingBuf> auto consume_one(RingBuf &buf) {
    claim(1);
    auto result = buf[current_];
    ++current_;
    return result;
  }

  void commit() { cursor_->move_to(current_ + 1); }

private:
  // size of ring buffer
  int size_;
  // local copy of cursor which we increment until committing
  int64_t current_;
  // store the last known follower position so that we
  // don't have to query it as often
  int64_t end_;
  std::shared_ptr<cursor> cursor_;
  std::shared_ptr<cursor> following_;
};

} // namespace meng

#endif
