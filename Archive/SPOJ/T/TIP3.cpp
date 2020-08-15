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

#include "collections/unique_counter.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/prime/segmented_prime_iterator.h"

const int CNT = 44;
const int ANSWERS[CNT] = {
    21,      63,      291,     2817,    2991,    4435,    20617,   45421,
    69271,   75841,   162619,  176569,  284029,  400399,  474883,  732031,
    778669,  783169,  1014109, 1288663, 1504051, 1514419, 1924891, 1956103,
    2006737, 2044501, 2094901, 2239261, 2710627, 2868469, 3582907, 3689251,
    4198273, 4696009, 5050429, 5380657, 5886817, 6018163, 6636841, 7026037,
    7357291, 7507321, 8316907, 8319823};
const int EASY_BOUND = 10000000;

const int PRIME_CNT = 3000000;
const int DELTA = 37558111;
const int DELTA_GAP = 50;
const int COMPLEMENTORY[9] = {1, 0, 8, 7, 6, 5, 4, 3, 2};

collections::UniqueCounter counter(10, 10);
vector<uint64_t> primes;
vector<int> primeMods, jumps, lasts;

const int DSUM_BOUND = 1000000;
vector<int> digitSums;

inline bool isValid(__int128_t n, __int128_t m) {
  int dsum = 0;
  for (__int128_t n0 = n; n0 > 0; n0 /= DSUM_BOUND) {
    dsum += digitSums[n0 % DSUM_BOUND];
  }
  for (__int128_t m0 = m; m0 > 0; m0 /= DSUM_BOUND) {
    dsum -= digitSums[m0 % DSUM_BOUND];
  }
  if (dsum) {
    return false;
  }
  counter.init(10);
  for (; n > 0; n /= 10) {
    counter.update(n % 10, 1);
  }
  for (; m > 0; m /= 10) {
    int digit = m % 10;
    counter.update(digit, -1);
    if (counter.cnts[digit] < 0) {
      return false;
    }
  }
  return counter.zeroCnt == 10;
}

inline __int128_t calc(__int128_t n, uint64_t bound) {
  if (n <= EASY_BOUND) {
    auto idx = upper_bound(ANSWERS, ANSWERS + CNT, n - 1) - ANSWERS;
    return !idx ? -1 : ANSWERS[idx - 1];
  }
  __int128_t res = -1;
  uint64_t lowerBound = bound >= DELTA ? bound - DELTA : 0,
           upperBound = bound + DELTA;
  int endIdx = static_cast<int>(
      lower_bound(primes.begin(), primes.end(), bound) - primes.begin());
  long double bestV = -1E100;
  int lastLowerGap = -1;
  for (int i = endIdx; i >= 0 && primes[i] >= lowerBound; --i) {
    lastLowerGap = primes[i] >= bound ? primes[i] - bound : bound - primes[i];
    uint64_t newUpperBound =
        min(min(upperBound, static_cast<uint64_t>(n / primes[i])),
            bound + lastLowerGap + DELTA_GAP);
    for (; endIdx < primes.size() && primes[endIdx] < newUpperBound; ++endIdx) {
    }
    uint64_t newLowerBound = max(lowerBound, bound + lastLowerGap - DELTA_GAP);
    int j, targetMod = COMPLEMENTORY[primeMods[i]];
    for (j = endIdx;
         j >= 0 && primes[j] >= newLowerBound && primeMods[j] != targetMod;
         --j) {}
    for (; j >= 0 && primes[j] >= newLowerBound; j = jumps[j]) {
      __int128_t subRes = static_cast<__int128_t>(primes[i]) * primes[j];
      if (subRes >= n) {
        continue;
      }
      int64_t den = primes[i] + primes[j] - 1;
      long double subBestV = static_cast<long double>(subRes) / den;
      if (bestV < subBestV &&
          isValid(
              subRes,
              static_cast<__int128_t>(primes[i] - 1) * (primes[j] - 1))) {
        bestV = subBestV;
        res = subRes;
      }
    }
  }
  return res;
}

inline void initPrimes() {
  primeMods.clear();
  jumps.clear();
  primeMods.reserve(primes.size());
  jumps.reserve(primes.size());
  lasts.assign(9, -1);
  int i = 0;
  for (uint64_t prime : primes) {
    int mod = prime % 9;
    primeMods.push_back(mod);
    jumps.push_back(lasts[mod]);
    lasts[mod] = i++;
  }
}

inline void initDigitSums() {
  digitSums.reserve(DSUM_BOUND);
  for (int i = 0; i < 10; ++i) {
    digitSums.push_back(i);
  }
  for (int i = 10; i < DSUM_BOUND; ++i) {
    digitSums.push_back(digitSums[i / 10] + i % 10);
  }
}

char s[100];

int main() {
  __int128_t n = 0;
  scanf("%s", s);
  int sl = strlen(s);
  for (int i = 0; i < sl; ++i) {
    n = n * 10 + s[i] - '0';
  }
  uint64_t bound = static_cast<uint64_t>(sqrt(n));
  math::SegmentedPrimeIterator<uint64_t> pi(bound + DELTA, DELTA << 1);
  primes.reserve(PRIME_CNT);
  pi.iterate(
      bound >= DELTA ? bound - DELTA : 0, bound + DELTA, [](uint64_t prime) {
        primes.push_back(prime);
      });
  initPrimes();
  initDigitSums();
  __int128_t res = calc(n, bound);
  if (res < 0) {
    io::writeCharArray("No solution.");
  } else {
    io::writeInt(res);
  }
  io::writeChar('\n');
  io::flusher.flush();
}
