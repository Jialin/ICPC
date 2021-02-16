// !macro_gen
// ALL MATRIX_MOD_INT_ALL
#pragma once

#include "math/mod/mod_int_macros.h" // INCLUDE

#include "common/macros.h"
#include "math/mod/mod_int.h"

namespace math {

template<typename V, typename V_SQR, V MOD>
struct MatrixModInt : public vector<vector<ModInt<V, V_SQR, MOD>>> {
  inline MatrixModInt(int n = 0, int m = 0) {
    init(n, m);
  }

  inline void init(int n, int m) {
    this->resize(n);
    FOR(i, 0, n) {
      (*this)[i].assign(m, 0);
    }
    _n = n;
    _m = m;
  }

#ifdef MATRIX_MOD_INT_SOLVE_MODIFY // ^
  inline void solveModify(vector<ModInt<V, V_SQR, MOD>>& b, vector<ModInt<V, V_SQR, MOD>>& res) {
    DEBUG_EQ(_n, _m);
    DEBUG_EQ(_n, b.size());
    FOR(i, 0, _n) {
      if (!(*this)[i][i]._v) {
        int row = -1;
        FOR(j, i + 1, _n) {
          if ((*this)[j][i]._v) {
            row = j;
            break;
          }
        }
        DEBUG_GE(row, 0);
        FOR(j, i, _n) {
          swap((*this)[i][j], (*this)[row][j]);
        }
        swap(b[i], b[row]);
      }
      // MATRIX_MOD_INT_SOLVE_MODIFY => MOD_INT_INV
      auto inv = (*this)[i][i].inv();
      if (inv._v != 1) {
        (*this)[i][i] = 1;
        FOR(j, i + 1, _n) {
          // MATRIX_MOD_INT_SOLVE_MODIFY => MOD_INT_MUL_INLINE
          (*this)[i][j] *= inv;
        }
        b[i] *= inv;
      }
      FOR(j, i + 1, _n) {
        if (!(*this)[j][i]._v) {
          continue;
        }
        b[j] -= b[i] * (*this)[j][i];
        for (int k = _n - 1; k >= i; --k) {
          // MATRIX_MOD_INT_SOLVE_MODIFY => MOD_INT_SUB_INLINE
          // MATRIX_MOD_INT_SOLVE_MODIFY => MOD_INT_MUL
          (*this)[j][k] -= (*this)[i][k] * (*this)[j][i];
        }
      }
    }
    for (int i = _n - 1; i >= 0; --i) {
      DEBUG_EQ((*this)[i][i]._v, 1);
      for (int j = i - 1; j >= 0; --j) {
        b[j] -= b[i] * (*this)[j][i];
        (*this)[j][i] = 0;
      }
    }
    if (res.size() < _n) {
      res.resize(_n);
    }
    FOR(i, 0, _n) {
      res[i] = b[i];
    }
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const MatrixModInt& vs) {
    o << "n:" << vs._n << " m:" << vs._m;
    FOR(i, 0, vs._n) {
      o << endl << tostring(static_cast<vector<ModInt<V, V_SQR, MOD>>>(vs[i]));
    }
    return o;
  }
#endif

  int _n, _m;
};

} // namespace math

#ifdef LOCAL
template<typename V, typename V_SQR, V MOD>
inline string totype(const math::MatrixModInt<V, V_SQR, MOD>& v) {
  return "MatrixModInt<" + totype(V()) + "," + totype(V_SQR()) + "," + tostring(MOD) + ">";
}
#endif
