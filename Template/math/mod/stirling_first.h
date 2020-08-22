#pragma once

#include <vector>

#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

struct StirlingFirst {
  inline StirlingFirst(int n, int mod) {
    init(n, mod);
  }

  inline void init(int n, int mod) {
    _mod = mod;
    _us.resize(n);
    int one = fixMod(1, mod);
    if (n > 0) {
      _us[0].assign(1, one);
    }
    for (int i = 1; i < n; ++i) {
      _us[i].resize(i + 1);
      _us[i][0] = 0;
      int i1 = fixMod(i - 1, mod);
      for (int j = 1; j < i; ++j) {
        _us[i][j] =
            addMod(mulMod(i1, _us[i - 1][j], mod), _us[i - 1][j - 1], mod);
      }
      _us[i][i] = one;
    }
  }

  inline int getUnsigned(int n, int k) {
    return n >= k ? _us[n][k] : 0;
  }

  inline int getSigned(int n, int k) {
    int res = getUnsigned(n, k);
    if (res && ((n - k) & 1)) {
      res = _mod - res;
    }
    return res;
  }

  vector<vector<int>> _us;
  int _mod;
};

} // namespace math
