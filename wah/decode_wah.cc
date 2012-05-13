#include "wah.hpp"
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

int main()
{
  typedef uint64_t value_type;
  typedef uint64_t word_type;

  typedef tzyah::wah::word_traits<word_type> tr;
  using tzyah::bit::count_bits;

  value_type base = 0;
  for (
      word_type w;
      cin.read(reinterpret_cast<char*>(&w), sizeof(w));
      base += tr::LITERAL_BITS
  ) {
    if (w & tr::LITERAL_FLAG) {

      for (w ^= tr::LITERAL_FLAG; w; w &= w - 1) {
        const value_type index = base + count_bits((w & (-w)) - 1);
        cout << hex << setw(16) << setfill('0') << index << endl;
      }

    } else if ((w & tr::FILL_MASK) == tr::ONE_FILL_FLAG) {

      const value_type runlen = (w & tr::RUNLEN_MASK) + 1;
      for (value_type i = 0; i < runlen; ++i) {
        cout << hex << setw(16) << setfill('0') << base + i << endl;
      }
      base += (runlen - 1) * tr::LITERAL_BITS;

    } else {
      base += w * tr::LITERAL_BITS;
    }

  }
  return 0;
}
