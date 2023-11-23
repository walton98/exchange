#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "types.hpp"

template <class T>
inline void write_to_file(const std::string &filename, T state) {
  std::ofstream ofs(filename);
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(state);
}

template <class T> inline T read_from_file(const std::string &filename) {
  std::ifstream ifs(filename);
  boost::archive::xml_iarchive ia(ifs);
  T state;
  ia >> boost::serialization::make_nvp("state", state);
  return state;
}
