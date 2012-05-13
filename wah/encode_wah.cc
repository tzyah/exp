#include "wah.hpp"

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
  typedef tzyah::wah::bitset<value_type, word_type> bitset_type;

  bitset_type b;

  for (uint64_t val; cin >> hex >> val; ) {
    b.set(val);
  }
  for (bitset_type::const_iterator it = b.begin(); it != b.end(); ++it) {
    cout.write(reinterpret_cast<const char*>(&*it), sizeof(*it));
  }
  return 0;
}
