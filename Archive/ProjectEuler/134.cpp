#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "io/write_int.h"
#include "math/constants.h"
#include "math/mod/exp.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"
#include "math/prime/segmented_prime_iterator.h"

using namespace std;

const int MAXN = 1000000000;
const int BUFFER = 1000;
const int MAXSPAN = 1000000 + BUFFER;

math::SegmentedPrimeIterator spi(MAXN);

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int lower, upper;
    scanf("%d%d", &lower, &upper);
    int lastP = -1;
    __int128 res = 0;
    int pow10 = 0;
    spi.iterate(
        lower,
        upper + BUFFER,
        [&lower, &upper, &lastP, &res, &pow10](int p) {
          if (p < lower) {
            return;
          }
          if (lastP >= 0) {
            for (; lastP > math::POW10[pow10]; ++pow10) {}
            long long x = math::mulMod(
                p - lastP, math::invMod(math::expMod(10, pow10, p), p), p);
            res += x * math::POW10[pow10] + lastP;
          }
          lastP = p <= upper ? p : -1;
        },
        MAXSPAN);
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
