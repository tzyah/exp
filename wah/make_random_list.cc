#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <boost/cstdint.hpp>

int main()
{
  using namespace std;
  for (srand48(time(NULL));;) {
    uint64_t r
      = ((static_cast<uint64_t>(lrand48()) << 33) & 0xc000000000000000UL)
      | (static_cast<uint64_t>(lrand48()) << 31)
      | lrand48();
    cout << hex << setw(16) << setfill('0') << r << endl;
  }
  return 0;
}
