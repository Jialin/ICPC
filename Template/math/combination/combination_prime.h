#pragma once

#include <vector>

#include "math/mod/fix.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Computes C(a, b) % (<modPrime> ^ <modExp>)
struct CombinationModPrime {
  inline CombinationModPrime() {}

  inline CombinationModPrime(int n, int modPrime, int modExp) {
    init(n, modPrime, modExp);
  }

  inline void init(int n, int modPrime, int modExp) {
    _modPrimePower.resize(modExp + 1);
    _modPrimePower[0] = 1;
    for (int i = 1; i <= modExp; ++i) {
      _modPrimePower[i] = _modPrimePower[i - 1] * modPrime;
    }
    _mod = _modPrimePower[modExp];
    _facs.clear();
    _facs.reserve(n);
    _cnts.clear();
    _cnts.reserve(n);
    _facs.push_back(1);
    _cnts.push_back(0);
    for (int i = 1; i < n; ++i) {
      int cnt = 0, tmpI = i;
      for (; tmpI >= modPrime && !(tmpI % modPrime); tmpI /= modPrime, ++cnt) {}
      _facs.push_back(mulMod(_facs.back(), fixMod(tmpI, _mod), _mod));
      _cnts.push_back(_cnts.back() + cnt);
    }
    _invFacs.reserve(n);
    _invFacs.resize(n);
    _invFacs[n - 1] = invMod(_facs[n - 1], _mod);
    for (int i = n - 1; i > 0; --i) {
      int tmpI = i;
      for (; tmpI >= modPrime && !(tmpI % modPrime); tmpI /= modPrime) {}
      _invFacs[i - 1] = mulMod(_invFacs[i], fixMod(tmpI, _mod), _mod);
    }
  }

  inline int calc(int n, int m) {
    if (n < m) {
      return 0;
    }
    int cntDiff = _cnts[n] - _cnts[m] - _cnts[n - m];
    if (cntDiff >= _modExp) {
      return 0;
    }
    return mulMod(
        mulMod(mulMod(_facs[n], _invFacs[m], _mod), _invFacs[n - m], _mod),
        _modPrimePower[cntDiff],
        _mod);
  }

  int _modPrime, _modExp, _mod;
  vector<int> _facs, _invFacs, _modPrimePower;
  vector<int> _cnts;
};

} // namespace math
