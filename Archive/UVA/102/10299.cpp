#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/prime/phi32.h"
#include "math/prime/prime_iterator.h"

const int BOUND = 31622;

math::PrimeIterator pi(BOUND);
vector<uint32_t> primes;

int main() {
  primes.reserve(3409);
  pi.iterate(BOUND, [](uint32_t p) {
    primes.push_back(p);
    return true;
  });
  int n;
  while (true) {
    io::readInt(n);
    if (!n) {
      break;
    }
    io::writeInt(n == 1 ? 0 : math::phi32(n, primes));
    io::writeChar('\n');
  }
}
