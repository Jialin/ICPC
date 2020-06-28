#include <cmath>
#include <cstring>
#include <functional>
#include <vector>

using namespace std;

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

class SegmentedPrimeIterator {
public:
  inline SegmentedPrimeIterator(int n = 30) {
    precompute_();
    init(n);
  }

  inline void init(int n) {
    int primeBound = static_cast<int>(sqrt(n) + 1);
    int size = primeBound / PRIME_LCM + 1;
    sieve_.assign(size, 0);
    sieve_[0] = 1;
    int bound = static_cast<int>(sqrt(primeBound) + 1);
    memcpy(mul_, mulInit_, sizeof(mul_));
    auto* sieve = sieve_.data();
    const auto* sieveEnd = sieve + size;
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

  inline void iterate(
      int lower,
      int upper,
      const std::function<void(int)>& processor,
      int maxRangeGap = -1) {
    if (maxRangeGap >= 0) {
      segmentedSieve_.reserve(maxRangeGap / PRIME_LCM + 2);
    }
    int lb = lower / PRIME_LCM;
    int ub = (upper + PRIME_LCM - 1) / PRIME_LCM;
    int offset = lb * PRIME_LCM;
    int size = ub - lb;
    segmentedSieve_.assign(size, 0);
    if (!lb) {
      segmentedSieve_[0] = 1;
    }
    memcpy(mul_, mulInit_, sizeof(mul_));
    const auto* sieve = sieve_.data();
    auto* segmentedSieveBegin = segmentedSieve_.data();
    const auto* segmentedSieveEnd = segmentedSieveBegin + size;
    bool exceeded = false;
    for (int base = 0; !exceeded; base += PRIME_LCM, ++sieve) {
      for (int i = 0; i < COPRIME_CNT; ++i) {
        if (!((*sieve >> i) & 1)) {
          int v = base + COPRIMES[i], vv = v * v;
          if (vv >= upper) {
            exceeded = true;
            break;
          }
          if (vv < offset) {
            vv += (offset - vv + v - 1) / v * v;
            vv += v * mulStep2_[i][vv % PRIME_LCM];
          }
          tag_(
              coprimesInv_[vv % PRIME_LCM],
              segmentedSieveBegin + (vv - offset) / PRIME_LCM,
              segmentedSieveEnd,
              mul_[i],
              nextIdx_[i]);
        }
        for (int k = 0; k < COPRIME_CNT; ++k) {
          mul_[i][k] += mulStep_[i][k];
        }
      }
    }
    for (int p : PRIME_WHEEL) {
      if (lower <= p && p < upper) {
        processor(p);
      }
    }
    const auto* segmentedSieve = segmentedSieve_.data();
    for (int base = offset; segmentedSieve < segmentedSieveEnd;
         base += PRIME_LCM, ++segmentedSieve) {
      for (int i = 0; i < COPRIME_CNT; ++i) {
        if ((*segmentedSieve >> i) & 1) {
          continue;
        }
        int v = base + COPRIMES[i];
        if (lower <= v && v < upper) {
          processor(v);
        }
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
      for (int j = 0; j < PRIME_LCM; ++j) {
        int sum = j, step = 0;
        for (; coprimesInv_[sum] < 0; ++step) {
          sum += COPRIMES[i];
          if (sum >= PRIME_LCM) {
            sum -= PRIME_LCM;
          }
        }
        mulStep2_[i][j] = step;
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
  int mulStep2_[COPRIME_CNT][PRIME_LCM];
  vector<long long> sieve_;
  vector<long long> segmentedSieve_;
};

} // namespace math
