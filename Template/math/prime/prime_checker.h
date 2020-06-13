#pragma once

#include <cmath>
#include <vector>

using namespace std;

namespace math {

class PrimeChecker {
public:
  inline PrimeChecker(int n) {
    init(n);
  }

  inline void init(int n) {
    int size = (n + 1) >> 1;
    isPrime_.assign(size, true);
    isPrime_[0] = false;
    int bound = static_cast<int>(sqrt(n) + 1);
    for (int i = 3; i <= bound; i += 2) {
      if (!isPrime_[i >> 1]) {
        continue;
      }
      for (int j = (i * i) >> 1; j < size; j += i) {
        isPrime_[j] = false;
      }
    }
  }

  inline bool isPrime(int x) {
    if (x == 2) {
      return true;
    }
    return (x & 1) && isPrime_[x >> 1];
  }

private:
  vector<bool> isPrime_;
};

} // namespace math
