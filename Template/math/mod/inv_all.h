#pragma once

#include <vector>

#include "math/mod/mul.h"

using namespace std;

namespace math {

// Calculate invMod(i,mod) for 1<=i<n
struct InvModAll {
  inline InvModAll(int n, int mod, int capacity = -1) {
    init(n, mod, capacity);
  }

  inline void init(int n, int mod, int capacity = -1) {
    if (capacity >= 0) {
      _invs.reserve(capacity);
    }
    _invs.resize(n);
    _invs[1] = 1;
    for (int i = 2; i < n; ++i) {
      _invs[i] = math::mulMod(mod / i, _invs[mod % i], mod);
      if (_invs[i]) {
        _invs[i] = mod - _invs[i];
      }
    }
  }

  inline int get(int i) {
    return _invs[i];
  }

  vector<int> _invs;
};

} // namespace math
