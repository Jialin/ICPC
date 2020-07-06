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
#include "math/prime/rho128.h"

int main() {
  srand(time(nullptr));
  __uint128_t n;
  io::readInt(n);
  math::MontgomeryMul mont(n);
  __uint128_t p = n;
  do {
    p = math::rho128(p, mont, false);
  } while (p == n);
  __uint128_t q = n / p;
  if (p < q) {
    io::writeInt(p);
    io::writeChar(' ');
    io::writeInt(q);
  } else {
    io::writeInt(q);
    io::writeChar(' ');
    io::writeInt(p);
  }
  io::writeChar('\n');
}
