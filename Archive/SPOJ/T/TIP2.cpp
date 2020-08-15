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
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/prime/prime_generator.h"

const int CNT = 44;
const int ANSWERS[CNT] = {
    21,      63,      291,     2817,    2991,    4435,    20617,   45421,
    69271,   75841,   162619,  176569,  284029,  400399,  474883,  732031,
    778669,  783169,  1014109, 1288663, 1504051, 1514419, 1924891, 1956103,
    2006737, 2044501, 2094901, 2239261, 2710627, 2868469, 3582907, 3689251,
    4198273, 4696009, 5050429, 5380657, 5886817, 6018163, 6636841, 7026037,
    7357291, 7507321, 8316907, 8319823};
const int EASY_BOUND = 10000000;

const int DELTA = 28915;
const int DELTA_GAP = 1106;
const uint64_t MAXN = 1000000000000ULL;
const int BOUND = static_cast<int>(sqrt(MAXN) + DELTA * 3);
const int COMPLEMENTORY[9] = {1, 0, 8, 7, 6, 5, 4, 3, 2};

const int PRIME_CNT = 82832;
math::PrimeGenerator generator(BOUND, PRIME_CNT);
collections::UniqueCounter counter(10, 10);
vector<int> primeMods, jumps, lasts;

const int DSUM_BOUND = 1000000;
vector<int> digitSums;

inline bool isValid(uint64_t n, uint64_t m) {
  if (digitSums[n / DSUM_BOUND] + digitSums[n % DSUM_BOUND] !=
      digitSums[m / DSUM_BOUND] + digitSums[m % DSUM_BOUND]) {
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

inline int64_t calc(uint64_t n) {
  const auto& primes = generator.primes;
  if (n <= EASY_BOUND) {
    auto idx = upper_bound(ANSWERS, ANSWERS + CNT, n - 1) - ANSWERS;
    return !idx ? -1 : ANSWERS[idx - 1];
  }
  int64_t res = -1;
  int bound = static_cast<int>(sqrt(n));
  int lowerBound = bound - DELTA, upperBound = bound + DELTA;
  int endIdx = static_cast<int>(
      lower_bound(primes.begin(), primes.end(), bound) - primes.begin());
  double bestV = -1E100;
  for (int i = endIdx; i >= 0 && primes[i] >= lowerBound; --i) {
    int lastLowerGap =
        primes[i] >= bound ? primes[i] - bound : bound - primes[i];
    int newUpperBound =
        min(min(upperBound, static_cast<int>(n / primes[i])),
            bound + lastLowerGap + DELTA_GAP);
    for (; primes[endIdx] < newUpperBound; ++endIdx) {}
    int j, targetMod = COMPLEMENTORY[primeMods[i]];
    int newLowerBound = max(lowerBound, bound + lastLowerGap - DELTA_GAP);
    for (j = endIdx;
         j >= 0 && primes[j] >= newLowerBound && primeMods[j] != targetMod;
         --j) {}
    for (; j >= 0 && primes[j] >= newLowerBound; j = jumps[j]) {
      uint64_t subRes = static_cast<uint64_t>(primes[i]) * primes[j];
      if (subRes >= n) {
        continue;
      }
      int den = primes[i] + primes[j] - 1;
      double subBestV = static_cast<double>(subRes) / den;
      if (bestV < subBestV &&
          isValid(subRes, (primes[i] - 1ULL) * (primes[j] - 1))) {
        bestV = subBestV;
        res = subRes;
      }
    }
  }
  return res;
}

inline void initPrimes() {
  primeMods.reserve(PRIME_CNT);
  jumps.reserve(PRIME_CNT);
  lasts.assign(9, -1);
  int i = 0;
  for (int prime : generator.primes) {
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

int main() {
  initPrimes();
  initDigitSums();
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    uint64_t n;
    io::readInt(n);
    int64_t res = calc(n);
    if (res < 0) {
      io::writeCharArray("No solution.");
    } else {
      io::writeInt(res);
    }
    io::writeChar('\n');
  }
  return 0;
}
