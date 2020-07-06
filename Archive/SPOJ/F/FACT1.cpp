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
#include "math/prime/factorize128.h"

int main() {
  math::MontgomeryMul mont;
  __uint128_t n;
  vector<pair<__uint128_t, int>> parts;
  const auto& processor = [&parts](__uint128_t prime, int exp) {
    parts.emplace_back(prime, exp);
  };
  while (true) {
    io::readInt(n);
    if (!n) {
      break;
    }
    parts.clear();
    math::factorize128(n, mont, processor);
    sort(parts.begin(), parts.end());
    bool first = true;
    for (const auto& part : parts) {
      if (!first) {
        io::writeChar(' ');
      } else {
        first = false;
      }
      io::writeInt(part.first);
      io::writeChar('^');
      io::writeInt(part.second);
    }
    io::writeChar('\n');
  }
}
