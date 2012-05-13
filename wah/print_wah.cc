#include "bit.hpp"

#include <boost/cstdint.hpp>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

using boost::uint64_t;
using boost::uint32_t;

typedef uint64_t index_type;
typedef uint64_t word_type;

int main()
{
  using tzyah::bit::count_bits;

  const size_t nbits = sizeof(word_type) * 8;
  for (word_type w; cin.read(reinterpret_cast<char*>(&w), sizeof(w)); ) {

    cout << hex << setw(16) << setfill('0') << w << '\t';

    bool is_literal = false;
    for (size_t i = 0; i < nbits; ++i) {
      int b = w & (static_cast<word_type>(1)<<(nbits - i - 1)) ? 1 : 0;
      cout << b;
      if (i == 0 && b) { is_literal = true; }
    }

    if (is_literal) {
      w -= static_cast<word_type>(1) << (nbits - 1);
      cout << "\tliteral: " << setw(16) << setfill('0') << w;
      cout << "\tbits: " << dec << count_bits(w);
    } else {
      ++w;
      cout << "\tfill:    " << dec << w;
    }
    cout << endl;

  }
  return 0;
}
