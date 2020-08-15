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
#include "math/mod/power_tower.h"
#include "math/prime/phi32.h"
#include "math/prime/prime_generator.h"

const int MAX_PRIME = 3402;

vector<int> bases, phis, vs;

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  math::PrimeGenerator generator(static_cast<int>(sqrt(m) + 10), MAX_PRIME);
  phis.push_back(m);
  while (phis.back() != 1) {
    phis.push_back(math::phi32(phis.back(), generator.primes));
  }
  bases.reserve(n);
  for (int i = 0; i < n; ++i) {
    int exp;
    io::readInt(exp);
    bases.push_back(exp);
  }
  int queryCnt;
  io::readInt(queryCnt);
  for (int i = 0; i < queryCnt; ++i) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    r = min(r, l + static_cast<int>(phis.size()));
    vs.clear();
    for (int j = l - 1; j < r; ++j) {
      vs.push_back(bases[j]);
    }
    io::writeInt(math::powerTower(vs, phis));
    io::writeChar('\n');
  }
  return 0;
}
