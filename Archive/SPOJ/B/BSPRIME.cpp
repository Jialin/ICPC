#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace io {

namespace {

const int kReadBufferSize = 1 << 15;
char readBuffer[kReadBufferSize];
int readPos;
int readLength;
bool ended = false;

inline void loadBuffer() {
  readLength =
      static_cast<int>(fread(readBuffer, sizeof(char), kReadBufferSize, stdin));
  readPos = 0;
}

} // namespace

inline char readChar(bool advance = true) {
  if (ended) {
    return 0;
  }
  if (readPos >= readLength) {
    loadBuffer();
    if (readLength == 0) {
      ended = true;
      return 0;
    }
  }
  return readBuffer[advance ? readPos++ : readPos];
}

} // namespace io

namespace io {

template<typename T>
inline bool readInt(T& res) {
  char ch;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (!isspace(ch)) {
      break;
    }
    ++readPos;
  }
  ch = readChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++readPos;
  }
  res = 0;
  while (true) {
    ch = readChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
    ++readPos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}

} // namespace io

namespace io {

namespace {

const int kWriteBufferSize = 1 << 15;

int writePos = 0;
char writeBuffer[kWriteBufferSize];

} // namespace

inline void writeChar(char x) {
  if (writePos == kWriteBufferSize) {
    fwrite(writeBuffer, 1, kWriteBufferSize, stdout);
    writePos = 0;
  }
  writeBuffer[writePos++] = x;
}

struct Flusher {
  inline ~Flusher() {
    if (writePos) {
      fwrite(writeBuffer, 1, writePos, stdout);
      writePos = 0;
    }
  }
} flusher;

} // namespace io

namespace io {

template<class T>
inline void writeInt(T x) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  for (; x || !n; x /= 10) {
    s[n++] = '0' + x % 10;
  }
  for (; n > 0; writeChar(s[--n])) {}
}

} // namespace io

struct Query {
  int n, idx;

  inline void init(int idx_) {
    io::readInt(n);
    idx = idx_;
  }

  inline bool operator<(const Query& o) const {
    return n < o.n;
  }
};

int taskNumber;
int queryIdx = 0;
int bc = 1, pow2 = 2;
int size = 0, oneCnt = 0;

const int MAXTASK = 50000;

Query queries[MAXTASK];
int answers[MAXTASK];

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

  inline void iterate(int n) {
    for (int i = 0; i < 4; ++i) {
      if (PRIME_WHEEL[i] < n) {
        process(PRIME_WHEEL[i]);
      }
    }
    int base = 0;
    long long* sieve = sieve_.data();
    const long long* sieveEnd = sieve + sieve_.size();
    for (; sieve < sieveEnd; ++sieve) {
      for (int idx = 0; idx < COPRIME_CNT; ++idx) {
        if ((*sieve >> idx) & 1) {
          continue;
        }
        int v = base + COPRIMES[idx];
        if (v >= n) {
          break;
        }
        process(v);
      }
      base += PRIME_LCM;
      if (base >= n) {
        break;
      }
    }
  }

  inline void process(int prime) {
    for (; prime >= pow2; ++bc, pow2 <<= 1) {}
    size += bc;
    oneCnt += __builtin_popcount(prime);
    for (; queryIdx < taskNumber && queries[queryIdx].n <= size; ++queryIdx) {
      int offset = size - queries[queryIdx].n;
      answers[queries[queryIdx].idx] =
          oneCnt - __builtin_popcount(prime - (prime >> offset << offset));
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

const int MAXBOUND = 101865020;

math::PrimeIterator pi(MAXBOUND);

int main() {
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    queries[taskIdx].init(taskIdx);
  }
  sort(queries, queries + taskNumber);
  pi.iterate(MAXBOUND);
  for (int i = 0; i < taskNumber; ++i) {
    io::writeInt(answers[i]);
    io::writeChar('\n');
  }
  return 0;
}
