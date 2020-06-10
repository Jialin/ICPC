#pragma once

using namespace std;

namespace math {

class PrimeChecker {
public:
  inline PrimeChecker(int n) {
    init(n);
  }

  inline void init(int n) {
    isPrime_.assign(n + 1, true);
    for (int i = 3; i <= n / i; i += 2) {
      if (!isPrime_[i]) {
        continue;
      }
      int ii = i << 1;
      for (int j = i * i; j <= n; j += ii) {
        isPrime_[j] = false;
      }
    }
  }

  inline bool check(int x) {
    if (x == 2) {
      return true;
    }
    return x > 2 && (x & 1) && isPrime_[x];
  }

private:
  vector<bool> isPrime_;
};

} // namespace math
