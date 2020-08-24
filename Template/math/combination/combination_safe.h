#pragma once

#include <vector>

#include "math/mod/fix.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Computes C(a, b) % <mod> where a<n, b<n, mod might be smaller than n
template<typename CNT = int>
struct CombinationModSafe {
  inline CombinationModSafe(int n, int mod) {
    init(n, mod);
  }

  inline void init(int n, int mod) {
    _mod = mod;
    _facs.clear();
    _facs.reserve(n);
    _cnts.clear();
    _cnts.reserve(n);
    _facs.push_back(mod != 1);
    _cnts.push_back(0);
    for (int i = 1; i < n; ++i) {
      int cnt = 0, tmpI = i;
      for (; !(tmpI % mod); tmpI /= mod, ++cnt) {}
      _facs.push_back(mulMod(_facs.back(), fixMod(tmpI, mod), mod));
      _cnts.push_back(_cnts.back() + cnt);
    }
    _invFacs.reserve(n);
    _invFacs.resize(n);
    _invFacs[n - 1] = invMod(_facs[n - 1], mod);
    for (int i = n - 1; i > 0; --i) {
      int tmpI = i;
      for (; !(tmpI % mod); tmpI /= mod) {}
      _invFacs[i - 1] = mulMod(_invFacs[i], fixMod(tmpI, mod), mod);
    }
  }

  inline int calc(int n, int m) {
    if (n < m || _cnts[n] > _cnts[m] + _cnts[n - m]) {
      return 0;
    }
    return mulMod(mulMod(_facs[n], _invFacs[m], _mod), _invFacs[n - m], _mod);
  }

  int _mod;
  vector<int> _facs, _invFacs;
  vector<CNT> _cnts;
};

} // namespace math
