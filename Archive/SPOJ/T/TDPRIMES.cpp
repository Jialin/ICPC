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

#include "io/write_int.h"
#include "math/prime/prime_iterator.h"

const int MAXN = 100000000;

math::PrimeIterator pi(MAXN);

int main() {
  int cnt = 99;
  pi.iterate(MAXN, [&cnt](int v) {
    if (cnt == 99) {
      io::writeInt(v);
      io::writeChar('\n');
      cnt = 0;
    } else {
      ++cnt;
    }
  });
}
