#pragma once

#include <cmath>
#include <vector>

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
  }

  inline int getMinPrimeFactor(int n) {
    if (n & 1) {
      int res = minPrime_[n >> 1];
      return res ? res : n;
    }
    return 2;
  }

private:
  vector<int> minPrime_;
};

} // namespace math
