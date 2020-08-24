#include <algorithm>
#include <vector>

#include "math/mod/inv.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Computes C(a, b) where a<=n and b<=n
struct CombinationMod {
  inline CombinationMod() {}

  inline CombinationMod(int n, int mod) {
    init(n, mod);
  }

  inline void init(int n, int mod) {
    _mod = mod;
    _facs.clear();
    _facs.reserve(n);
    int j = mod != 1;
    _facs.push_back(j);
    for (int i = 1; i < n; ++i) {
      _facs.push_back(mulMod(_facs.back(), j, mod));
      j = j + 1 == mod ? 0 : j + 1;
    }
    _invFacs.reserve(n);
    _invFacs.resize(n);
    _invFacs[n - 1] = invMod(_facs[n - 1], mod);
    for (int i = n - 1; i > 0; --i) {
      j = !j ? mod - 1 : j - 1;
      _invFacs[i - 1] = mulMod(_invFacs[i], j, mod);
    }
  }

  inline int calc(int n, int m) {
    if (n < m) {
      return 0;
    }
    return mulMod(mulMod(_facs[n], _invFacs[m], _mod), _invFacs[n - m], _mod);
  }

  int _mod;
  vector<int> _facs, _invFacs;
};

} // namespace math
