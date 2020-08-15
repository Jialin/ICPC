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
#include <utility>
#include <vector>

using namespace std;

#include "io/read_int.h"
#include "io/write_int.h"

const int MAXN = 10000000 + 1;
const int BOUND = 3163;

vector<int> primes;

namespace math {

namespace {

const int PRIME_WHEEL[4] = {2, 3, 5, 7};
const int PRIME_LCM = 2 * 3 * 5 * 7;
const int COPRIME_CNT = 48;
const int COPRIMES[COPRIME_CNT] = {
    1,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,
    53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103,
    107, 109, 113, 121, 127, 131, 137, 139, 143, 149, 151, 157,
    163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209};

} // namespace

class PrimeIterator {
public:
  inline PrimeIterator(int n = 30) {
    precompute_();
    init(n);
  }

  inline void init(int n) {
    int size = n / PRIME_LCM + 1;
    sieve_.assign(size, 0);
    sieve_[0] = 1;
    int bound = static_cast<int>(sqrt(n) + 1);
    memcpy(mul_, mulInit_, sizeof(mul_));
    long long* sieve = sieve_.data();
    const long long* sieveEnd = sieve + size;
    for (int base = 0; base <= bound; base += PRIME_LCM, ++sieve) {
      for (int i = 0; i < COPRIME_CNT; ++i) {
        if (!((*sieve >> i) & 1)) {
          int v = base + COPRIMES[i], vv = v * v;
          tag_(
              coprimesInv_[vv % PRIME_LCM],
              sieve_.data() + vv / PRIME_LCM,
              sieveEnd,
              mul_[i],
              nextIdx_[i]);
        }
        for (int k = 0; k < COPRIME_CNT; ++k) {
          mul_[i][k] += mulStep_[i][k];
        }
      }
    }
  }

  inline void iterate(int n) const {
    if (PRIME_WHEEL[0] < n) {
      primes.push_back(PRIME_WHEEL[0]);
    }
    if (PRIME_WHEEL[1] < n) {
      primes.push_back(PRIME_WHEEL[1]);
    }
    if (PRIME_WHEEL[2] < n) {
      primes.push_back(PRIME_WHEEL[2]);
    }
    if (PRIME_WHEEL[3] < n) {
      primes.push_back(PRIME_WHEEL[3]);
    }
    int base = 0;
    for (int i = 0; i < sieve_.size(); ++i) {
      const long long sieve = sieve_[i];
      for (int idx = 0; idx < COPRIME_CNT; ++idx) {
        if ((sieve >> idx) & 1) {
          continue;
        }
        int v = base + COPRIMES[idx];
        if (v >= n) {
          break;
        }
        primes.push_back(v);
      }
      base += PRIME_LCM;
      if (base >= n) {
        break;
      }
    }
  }

private:
  inline void precompute_() {
    memset(coprimesInv_, 0xFF, sizeof(coprimesInv_));
    for (int i = 0; i < COPRIME_CNT; ++i) {
      coprimesInv_[COPRIMES[i]] = i;
    }
    for (int i = 0; i < COPRIME_CNT; ++i) {
      for (int j = 0; j < COPRIME_CNT; ++j) {
        int sum = COPRIMES[i] + COPRIMES[j], step = 1, delta = 0;
        if (sum >= PRIME_LCM) {
          sum -= PRIME_LCM;
          ++delta;
        }
        for (; coprimesInv_[sum] < 0; ++step) {
          sum += COPRIMES[i];
          if (sum >= PRIME_LCM) {
            sum -= PRIME_LCM;
            ++delta;
          }
        }
        nextIdx_[i][j] = coprimesInv_[sum];
        mulInit_[i][j] = delta;
        mulStep_[i][j] = step;
      }
    }
  }

  inline void tag_(
      int idx,
      long long* sieve,
      const long long* sieveEnd,
      const int* mul,
      const int* nextIdx) {
    while (sieve < sieveEnd) {
      *sieve |= 1LL << idx;
      sieve += mul[idx];
      idx = nextIdx[idx];
    }
  }

  int mul_[COPRIME_CNT][COPRIME_CNT];
  int coprimesInv_[PRIME_LCM];
  int mulInit_[COPRIME_CNT][COPRIME_CNT];
  int mulStep_[COPRIME_CNT][COPRIME_CNT];
  int nextIdx_[COPRIME_CNT][COPRIME_CNT];
  vector<long long> sieve_;
};

} // namespace math

namespace math {

// Provides all primes less than sqrt(n)
int phi32(int n, const vector<int>& primes) {
  int res = n;
  for (int i = 0; i < primes.size(); ++i) {
    int prime = primes[i];
    if (prime > n / prime) {
      break;
    }
    if (n % prime) {
      continue;
    }
    res -= res / prime;
    for (n /= prime; !(n % prime); n /= prime) {}
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

} // namespace math

math::PrimeIterator primeIterator(BOUND);

int main() {
  primes.reserve(446);
  primeIterator.iterate(BOUND);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    scanf("%d", &n);
    io::readInt(n);
    io::writeInt(n == 30 ? 64 : math::phi32(n, primes));
    io::writeChar('\n');
  }
  return 0;
}
