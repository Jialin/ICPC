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

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

using namespace std;

vector<pair<int, int>> results;

namespace math {

class MinPrimeTagger {
public:
  inline MinPrimeTagger(int n) {
    init(n);
  }

  inline void init(int n) {
    int size = n >> 1;
    minPrime_.assign(size, 0);
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
    len_.assign(size, 1);
    len_[0] = 0;
    for (int i = 3, j = 1; i < n; i += 2, ++j) {
      if (!minPrime_[j]) {
        continue;
      }
      len_[j] = len_[(i / minPrime_[j]) >> 1] + 1;
    }
    results.reserve(n);
    for (int i = 1, j = 0; i < n; i += 2, ++j) {
      results.push_back({len_[j], i});
    }
    for (int i = 2; i < n; i += 2) {
      int pow2 = __builtin_ctz(i);
      results.push_back({len_[(i >> pow2) >> 1] + pow2, i});
    }
    sort(results.begin(), results.end());
  }

private:
  vector<int> minPrime_;
  vector<int> len_;
};

} // namespace math

const int MAXN = 2000000 + 1;

math::MinPrimeTagger mpt(MAXN);

int main() {
  for (int i = 1;; ++i) {
    int n;
    io::readInt(n);
    if (!n) {
      break;
    }
    io::writeCharArray("Case ");
    io::writeInt(i);
    io::writeCharArray(": ");
    io::writeInt(results[n - 1].second);
    io::writeChar('\n');
  }
  return 0;
}
