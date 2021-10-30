#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseSparseTable2D {
  virtual inline void combineLeftRight(const V& leftValue, const V& rightValue, V& res) const = 0;

  virtual inline void combineUpperLower(const V& upperValue, const V& lowerValue, V& res) const = 0;

  inline void init(vector<vector<V>>&& vs) {
    int n = vs.size();
    int m = vs.empty() ? 0 : vs.front().size();
    int nm = max(n, m);
    if (!nm) {
      return;
    }
    _initLog(nm);
    int boundN = _log[n] + 1;
    int boundM = _log[m] + 1;
    _st.resize(boundN);
    FOR(bitN, 0, boundN) {
      _st[bitN].resize(boundM);
      FOR(bitM, 0, boundM) {
        auto& rows = _st[bitN][bitM];
        if (!bitN && !bitM) {
          rows = move(vs);
          continue;
        }
        rows.resize(n);
        for (auto& row : rows) {
          row.resize(m);
        }
        int sizeN = n - (1 << bitN) + 1;
        int sizeM = m - (1 << bitM) + 1;
        auto& prevRows = bitM ? _st[bitN][bitM - 1] : _st[bitN - 1][bitM];
        FOR(i, 0, sizeN) FOR(j, 0, sizeM) {
          if (bitM) {
            combineLeftRight(prevRows[i][j], prevRows[i][j + (1 << (bitM - 1))], rows[i][j]);
          } else {
            combineUpperLower(prevRows[i][j], prevRows[i + (1 << (bitN - 1))][j], rows[i][j]);
          }
        }
      }
    }
  }

  inline V calc(int x1, int y1, int x2, int y2) {
    DEBUG_LT(x1, x2);
    DEBUG_LT(y1, y2);
    int bitN = _log[x2 - x1];
    int bitM = _log[y2 - y1];
    const auto& rows = _st[bitN][bitM];
    V res;
    if (bitN) {
      if (bitM) {
        V upperRes;
        combineLeftRight(rows[x1][y1], rows[x1][y2 - (1 << bitM)], upperRes);
        V lowerRes;
        combineLeftRight(
            rows[x2 - (1 << bitN)][y1], rows[x2 - (1 << bitN)][y2 - (1 << bitM)], lowerRes);
        combineUpperLower(upperRes, lowerRes, res);
      } else {
        combineUpperLower(rows[x1][y1], rows[x2 - (1 << bitN)][y1], res);
      }
    } else {
      if (bitM) {
        combineLeftRight(rows[x1][y1], rows[x1][y2 - (1 << bitM)], res);
      } else {
        res = rows[x1][y1];
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

  vector<vector<vector<vector<V>>>> _st;
  vector<int> _log;
};

} // namespace ds
