#ifndef MENG_CONSUMER_HPP
#define MENG_CONSUMER_HPP

#include <iostream>
#include <string>

#include <meng.pb.h>
#include <server/consumer.hpp>

namespace meng {

class consumer : public server::consumer<consumer> {
  friend server::consumer<consumer>;
  using server::consumer<consumer>::consumer;

  void handle_message(std::string data);
};

} // namespace meng

#endif // MENG_CONSUMER_HPP
