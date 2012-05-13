#ifndef BIT_HPP__
#define BIT_HPP__

#include <boost/cstdint.hpp>

namespace tzyah { namespace bit {

  using boost::uint64_t;
  using boost::uint32_t;

  inline uint64_t count_bits(uint64_t b)
  {
    b = (b & 0x5555555555555555) + (b >> 1 & 0x5555555555555555);
    b = (b & 0x3333333333333333) + (b >> 2 & 0x3333333333333333);
    b = (b & 0x0f0f0f0f0f0f0f0f) + (b >> 4 & 0x0f0f0f0f0f0f0f0f);
    b = (b & 0x00ff00ff00ff00ff) + (b >> 8 & 0x00ff00ff00ff00ff);
    b = (b & 0x0000ffff0000ffff) + (b >> 16 & 0x0000ffff0000ffff);
    return (b & 0x00000000ffffffff) + (b >> 32 & 0x00000000ffffffff);
  }

  inline uint32_t count_bits(uint32_t b)
  {
    b = (b & 0x55555555) + (b >> 1 & 0x55555555);
    b = (b & 0x33333333) + (b >> 2 & 0x33333333);
    b = (b & 0x0f0f0f0f) + (b >> 4 & 0x0f0f0f0f);
    b = (b & 0x00ff00ff) + (b >> 8 & 0x00ff00ff);
    return b = (b & 0x0000ffff) + (b >> 16 & 0x0000ffff);
  }

}}
#endif
