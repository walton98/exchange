#include <iostream>

#include <server/consumer.hpp>

namespace meng {

class consumer : public server::consumer<consumer> {
  friend server::consumer<consumer>;
  using server::consumer<consumer>::consumer;

  void handle_message(char data[]) {
    std::cout << "handled message " << data << std::endl;
  }
};

}
