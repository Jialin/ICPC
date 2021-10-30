#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename V, int MAXNBIT, int MAXMBIT, int MAXN, int MAXM>
struct BaseSparseTable2DArray {
  virtual inline void combineLeftRight(const V& leftValue, const V& rightValue, V& res) const = 0;

  virtual inline void combineUpperLower(const V& upperValue, const V& lowerValue, V& res) const = 0;

  inline void init(vector<vector<V>>&& vs) {
    DEBUG_LT(MAXN, 1 << MAXNBIT);
    DEBUG_LT(MAXM, 1 << MAXMBIT);
    int n = vs.size();
    int m = vs.empty() ? 0 : vs.front().size();
    int nm = max(n, m);
    if (!nm) {
      return;
    }
    _initLog(nm);
    int boundN = _log[n] + 1;
    int boundM = _log[m] + 1;
    FOR(bitN, 0, boundN) FOR(bitM, 0, boundM) {
      if (bitN) {
        int sizeM = m - (1 << bitM) + 1;
        for (int i = 0, ii = 1 << (bitN - 1); ii < n; ++i, ++ii) {
          FOR(j, 0, sizeM) {
            combineUpperLower(
                _st[bitN - 1][bitM][i][j], _st[bitN - 1][bitM][ii][j], _st[bitN][bitM][i][j]);
          }
        }
      } else if (bitM) {
        int sizeN = n - (1 << bitN) + 1;
        FOR(i, 0, sizeN) {
          for (int j = 0, jj = 1 << (bitM - 1); jj < m; ++j, ++jj) {
            combineLeftRight(
                _st[bitN][bitM - 1][i][j], _st[bitN][bitM - 1][i][jj], _st[bitN][bitM][i][j]);
          }
        }
      } else {
        FOR(i, 0, n) FOR(j, 0, m) {
          _st[bitN][bitM][i][j] = move(vs[i][j]);
        }
      }
    }
  }

  inline V calc(int x1, int y1, int x2, int y2) {
    int bitN = _log[x2 - x1];
    int bitM = _log[y2 - y1];
    x2 -= 1 << bitN;
    y2 -= 1 << bitM;
    V res;
    if (bitN) {
      if (bitM) {
        V upperRes;
        combineLeftRight(_st[bitN][bitM][x1][y1], _st[bitN][bitM][x1][y2], upperRes);
        V lowerRes;
        combineLeftRight(_st[bitN][bitM][x2][y1], _st[bitN][bitM][x2][y2], lowerRes);
        combineUpperLower(upperRes, lowerRes, res);
      } else {
        combineUpperLower(_st[bitN][bitM][x1][y1], _st[bitN][bitM][x2][y2], res);
      }
    } else {
      if (bitM) {
        combineLeftRight(_st[bitN][bitM][x1][y1], _st[bitN][bitM][x2][y2], res);
      } else {
        return _st[bitN][bitM][x1][y1];
      }
    }
    return res;
  }

  inline void _initLog(int capacity) {
    int oldSize = _log.size();
    if (capacity <= oldSize) {
      return;
    }
    _log.resize(capacity + 1);
    _log[1] = 0;
    FOR(i, max(2, oldSize), capacity + 1) {
      _log[i] = _log[i >> 1] + 1;
    }
  }

  V _st[MAXNBIT][MAXMBIT][MAXN][MAXM];
  vector<int> _log;
};

} // namespace ds
