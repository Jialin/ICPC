#pragma once

#include <vector>

using namespace std;

class PhiAll {
public:
  inline PhiAll(int n) {
    init(n);
  }

  inline void init(int n) {
    int size = (n + 1) >> 1;
    phi_.resize(size);
    for (int i = 1; i < n; i += 2) {
      phi_[i >> 1] = i;
    }
    for (int i = 3, j = 1; i < n; i += 2, ++j) {
      if (phi_[j] != i) {
        continue;
      }
      --phi_[j];
      for (int k = 3 * j + 1; k < size; k += i) {
        phi_[k] -= phi_[k] / i;
      }
    }
  }

  inline int get(int n) {
    if (n & 1) {
      return phi_[n >> 1];
    }
    int shift = __builtin_ctz(n);
    return (phi_[n >> shift >> 1] << shift) >> 1;
  }

private:
  vector<int> phi_;
};
