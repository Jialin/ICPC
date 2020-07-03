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

#include "io/read_int.h"
#include "io/write_int.h"

const int MAXN = 10;

using namespace std;

namespace math {

class MinPrimeTagger {
public:
  inline MinPrimeTagger(int n) {
    init(n);
  }

  inline void init(int n) {
    int size = (n + 1) >> 1;
    minPrime_.assign(size, 0);
    cnt_.assign(size, 0);
    int bound = static_cast<int>(sqrt(n) + 1);
    for (int i = 3; i <= bound; i += 2) {
      if (minPrime_[i >> 1]) {
        continue;
      }
      for (int j = (i * i) >> 1; j < size; j += i) {
        if (!minPrime_[j]) {
          minPrime_[j] = i;
        }
      }
    }
    results[0].push_back(1);
    for (int i = 2; i <= n; ++i) {
      int cnt = 0;
      if (i & 1) {
        auto& p = minPrime_[i >> 1];
        if (!p) {
          p = i;
        }
        int j = i / p;
        cnt = cnt_[j >> 1] + (p != minPrime_[j >> 1]);
        cnt_[i >> 1] = cnt;
      } else {
        cnt = cnt_[(i >> __builtin_ctz(i)) >> 1] + 1;
      }
      if (cnt <= MAXN) {
        results[cnt].push_back(i);
      }
    }
  }

  vector<int> results[MAXN + 1];

private:
  vector<int> minPrime_, cnt_;
};

} // namespace math

const int MAXV = 1000000;

math::MinPrimeTagger mpt(MAXV);

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int a, b, n;
    io::readInt(a);
    io::readInt(b);
    io::readInt(n);
    auto& result = mpt.results[n];
    io::writeInt(
        upper_bound(result.begin(), result.end(), b) -
        lower_bound(result.begin(), result.end(), a));
    io::writeChar('\n');
  }
  return 0;
}
