#include <iostream>

#include <server/consumer.hpp>

namespace meng {

class consumer : public server::consumer {
  using server::consumer::consumer;

  void handle_message(char data[]) {
    std::cout << "handled message " << data << std::endl;
  }
};

}
